#include "mbed.h" /* Release 150 */
#include "sdk/hardware/mpu9255.h"
#include "data_structures/imu_buffer.h"
#include "tools/error_handler.h"
#include "tools/global_def.h"

#define IMU_SAMPLES_NR 8000

struct ImuSample imu_samples[IMU_SAMPLES_NR];

enum DeviceState {
    DEVSTATE_DISABLED,
    DEVSTATE_READY_FOR_ACQUISITION,
    DEVSTATE_ACQUIRING,
    DEVSTATE_INTERRUPTED,
    DEVSTATE_READY_FOR_TRANSMISSION,
    DEVSTATE_TRANSMITTING,
    DEVSTATE_DONE
};

InterruptIn userButton(USER_BUTTON);
DigitalOut successLed(LED1);
Serial pc(PA_9, PA_10);
Ticker t;
volatile bool processing_next_data_allowed;
volatile enum DeviceState device_state;

bool isButtonPressed()
{
    return userButton.read() == 0;
}

void allow_processing_data()
{
    if (!processing_next_data_allowed)
    {
        processing_next_data_allowed = true;
    }
    else
    {
        /* data reading from imu sensor is too slow */
        process_error();
    }
}

void acquire_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();    
        
    uint8_t regs_read[6];
    struct ImuSample new_sample;

    t.attach(&allow_processing_data, 0.001);
    
    while (1)
    {
        if (device_state == DEVSTATE_INTERRUPTED &&
                    buf_is_ready_for_read(buf))
            break;
        if (!processing_next_data_allowed)
            continue;
        
        mpu9255_accel_read_data_regs(regs_read);
        new_sample.accel_x = (uint16_t)((regs_read[0] << 8) + regs_read[1]);
        new_sample.accel_y = (uint16_t)((regs_read[2] << 8) + regs_read[3]);
        new_sample.accel_z = (uint16_t)((regs_read[4] << 8) + regs_read[5]);
        
        mpu9255_gyro_read_data_regs(regs_read);
        new_sample.gyro_x = (uint16_t)((regs_read[0] << 8) + regs_read[1]);
        new_sample.gyro_y = (uint16_t)((regs_read[2] << 8) + regs_read[3]);
        new_sample.gyro_z = (uint16_t)((regs_read[4] << 8) + regs_read[5]);
        
        buf_replace_next(buf, &new_sample);
        
        processing_next_data_allowed = false;
    }
    
    t.detach();
}

void send_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();
     
     
    struct ImuSample new_sample;
    do
    {
        buf_read_next(buf, &new_sample);
        
        pc.printf("%04x%04x%04x",
            new_sample.accel_x,
            new_sample.accel_y,
            new_sample.accel_z);
            
        pc.printf("%04x%04x%04x",
            new_sample.gyro_x,
            new_sample.gyro_y,
            new_sample.gyro_z);
            
        pc.printf("\r");   
    
    } while (!buf_is_all_data_read(buf));
}

void user_button_handler(void)
{
    if (device_state == DEVSTATE_ACQUIRING)
    {
        device_state = DEVSTATE_INTERRUPTED;        
    }
}

int main()
{
    static struct ImuBuffer* imu_samples_buf = buf_create(ARRAY_LEN(imu_samples), imu_samples);
    if (!imu_samples_buf)
        process_error();
    
    device_state = DEVSTATE_DISABLED;
    pc.baud(115200);
    mpu9255_init();
    
    while(1)
    {
        device_state = DEVSTATE_READY_FOR_ACQUISITION;
        while(!isButtonPressed())
            ;
            
        successLed.write(1);
        wait(0.5);
        successLed.write(0);
        
        device_state = DEVSTATE_ACQUIRING;
        userButton.rise(&user_button_handler);
        
        acquire_imu_samples(imu_samples_buf);
        
        userButton.rise(NULL);
        
        device_state = DEVSTATE_READY_FOR_TRANSMISSION;
        successLed.write(1);
        wait(0.5);
        
        while(!isButtonPressed())
            ;
        
        device_state = DEVSTATE_TRANSMITTING;
        send_imu_samples(imu_samples_buf);
        
        device_state = DEVSTATE_DONE;
        successLed.write(0);
    }
}

