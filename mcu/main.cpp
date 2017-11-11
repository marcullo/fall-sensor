#include "mbed.h" /* Release 150 */
#include "sdk/hardware/mpu9255.h"
#include "data_structures/imu_buffer.h"
#include "tools/error_handler.h"
#include "tools/global_def.h"
#include "command_decoder/command_decoder.h"

#define IMU_SAMPLES_NR          8000
#define COLLECTING_FREQUENCY    1000
#define COLLECTING_TIME         (float)((float)1/(float)COLLECTING_FREQUENCY)

struct ImuSample imu_samples[IMU_SAMPLES_NR];

#define HELLO_MESSAGE      "FSHELLO2017MARCULLO\r"

char message[COMMAND_MAX_LEN];

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
    uint32_t cnt = 0;
    struct ImuSample new_sample;

    t.attach(&allow_processing_data, COLLECTING_TIME);
    
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
        
        cnt++;
        if (cnt > IMU_SAMPLES_NR - 1)
        {
            successLed = !successLed;
            cnt = 0;
        }
    }
    
    t.detach();
}

void send_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();
     
    
    pc.printf("FS%04x", IMU_SAMPLES_NR);
    
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
    } while (!buf_is_all_data_read(buf));
    
    pc.printf("\r");
}

void send_packets_nr()
{
    pc.printf("FS0001\r");    
}

void send_frequency()
{
    pc.printf("FS%04x\r", COLLECTING_FREQUENCY);
}

void user_button_handler(void)
{
    if (device_state == DEVSTATE_ACQUIRING)
    {
        device_state = DEVSTATE_INTERRUPTED;        
    }
}

void process_pc_commands(struct ImuBuffer* samples)
{
    while(1) 
    {
        memset(message, 0, sizeof(message));
        pc.scanf("%s", message);
        
        enum CommandCode command = decode_message(message);
        switch (command)
        {
        case FS_HELLO:
            pc.printf(HELLO_MESSAGE);
            break;
            
        case FS_RESET:
            NVIC_SystemReset();
            break;
            
        case FS_PACKETS_NR:
            send_packets_nr();
            break;
            
        case FS_FREQUENCY:
            send_frequency();
            break;
        
        case FS_PACKETS:
            send_imu_samples(samples);
            break;
            
        default:
            break;            
        }
    }
}

int main()
{
    static struct ImuBuffer* imu_samples_buf = buf_create(ARRAY_LEN(imu_samples), imu_samples);
    if (!imu_samples_buf)
        process_error();
    
    device_state = DEVSTATE_DISABLED;
    pc.baud(921600);
    pc.format(8, SerialBase::Even);
    mpu9255_init();
    
    while(1)
    {
        device_state = DEVSTATE_READY_FOR_ACQUISITION;
            
        successLed.write(1);
        wait(0.5);
        device_state = DEVSTATE_ACQUIRING;
        userButton.rise(&user_button_handler);
        successLed.write(0);
        
        acquire_imu_samples(imu_samples_buf);
        
        userButton.rise(NULL);
        
        device_state = DEVSTATE_READY_FOR_TRANSMISSION;
        successLed = !successLed;
        wait(0.4);
        successLed = !successLed;

        process_pc_commands(imu_samples_buf);
    }
}

