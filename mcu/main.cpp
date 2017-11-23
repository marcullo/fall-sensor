#include "mbed.h" /* Release 150 */
#include "SDFileSystem.h" /* 9 Sep 2016 */
#include "sdk/hardware/mpu9255.h"
#include "imu_buffer/imu_buffer.h"
#include "tools/error_handler.h"
#include "tools/global_def.h"
#include "command_decoder/command_decoder.h"

#define DISC_NAME "sd"

#define IMU_SAMPLES_NR          5000
#define COLLECTING_FREQUENCY    1000
#define COLLECTING_TIME         (float)((float)1/(float)COLLECTING_FREQUENCY)

struct ImuSample imu_samples[IMU_SAMPLES_NR];
uint32_t collected_samples_nr;

#define HELLO_MESSAGE      "FSHELLO2017MARCULLO\r"

char message[COMMAND_MAX_LEN];

enum DeviceState {
    DEVSTATE_DISABLED,
    DEVSTATE_READY_FOR_ACQUISITION,
    DEVSTATE_ACQUIRING,
    DEVSTATE_INTERRUPTED
};

InterruptIn userButton(USER_BUTTON);
InterruptIn imuIntPin(PC_9);
DigitalOut successLed(PC_0);
SDFileSystem sd(PA_7, PA_6, PB_3, PB_6, DISC_NAME);
PwmOut buzzer(PA_8);
Serial pc(PA_9, PA_10);
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

volatile bool newDataAvailable = false;

void imu_interrupt_handler()
{
    newDataAvailable = true;
}

void acquire_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();    
        
    uint8_t regs_read[6];
    uint32_t cnt = 0;
    struct ImuSample new_sample;

    imuIntPin.fall(&imu_interrupt_handler);
    
    collected_samples_nr = 0;
    while (1)
    {
        if (device_state == DEVSTATE_INTERRUPTED)
            break;
        if(!newDataAvailable)
            continue;
        newDataAvailable = false;
                    
        mpu9255_accel_read_data_regs(regs_read);
        new_sample.accel_x = (uint16_t)(((uint16_t)regs_read[0] << 8) + regs_read[1]);
        new_sample.accel_y = (uint16_t)(((uint16_t)regs_read[2] << 8) + regs_read[3]);
        new_sample.accel_z = (uint16_t)(((uint16_t)regs_read[4] << 8) + regs_read[5]);
        
        mpu9255_gyro_read_data_regs(regs_read);
        new_sample.gyro_x = (uint16_t)(((uint16_t)regs_read[0] << 8) + regs_read[1]);
        new_sample.gyro_y = (uint16_t)(((uint16_t)regs_read[2] << 8) + regs_read[3]);
        new_sample.gyro_z = (uint16_t)(((uint16_t)regs_read[4] << 8) + regs_read[5]);
        
        buf_replace_next(buf, &new_sample);
        
        processing_next_data_allowed = false;
        
        if (collected_samples_nr < IMU_SAMPLES_NR)
            collected_samples_nr++;
        
        cnt++;
        if (cnt >= IMU_SAMPLES_NR)
        {
            successLed = !successLed;
            cnt = 0;
        }    
    }
    
    imuIntPin.fall(NULL);
}

void save_imu_samples(struct ImuBuffer* buf)
{
    static uint32_t packet_nr = 0;
    
    if (!buf)
        return;
        
    char file_path[20];
    sprintf(file_path, "/%s/%04x.dat", DISC_NAME, packet_nr);
    
    FILE* f = fopen(file_path, "w");
    if (!f)
        process_error();
    
    pc.printf("\r\nSaving (%d samples) to: %s\r\n", collected_samples_nr, file_path);
    
    fprintf(f, "FS%04x", collected_samples_nr);
    
    struct ImuSample new_sample;
    while(!buf_is_empty(buf))
    {
        buf_read_next(buf, &new_sample);
        
        fprintf(f, "%04x%04x%04x",
            new_sample.accel_x,
            new_sample.accel_y,
            new_sample.accel_z);
            
        fprintf(f, "%04x%04x%04x",
            new_sample.gyro_x,
            new_sample.gyro_y,
            new_sample.gyro_z);
    }
    
    pc.printf("\r\nSaved!\r\n");
    
    fprintf(f, "\r\n");

    fclose(f);
    
    collected_samples_nr = 0;
    packet_nr++;
}

void send_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();
     
    
    pc.printf("FS%04x", collected_samples_nr);
    
    struct ImuSample new_sample;
    while(!buf_is_empty(buf))
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
    }
    
    pc.printf("\r");
    
    collected_samples_nr = 0;
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
    
    buzzer.period(1.0f);
    buzzer.write(0.25f);
    wait(1.0);
    
    while(1)
    {        
        device_state = DEVSTATE_READY_FOR_ACQUISITION;    
        
        device_state = DEVSTATE_ACQUIRING;
        userButton.fall(&user_button_handler);
        
        successLed = !successLed;
        buzzer.write(0.0f);        
        
        acquire_imu_samples(imu_samples_buf);
        
        userButton.fall(NULL);
        
        successLed = !successLed;
        wait(0.5);

        if (isButtonPressed())
        {
            buzzer.write(0.25f);
            wait(1.0);
            buzzer.write(0.0f);
            process_pc_commands(imu_samples_buf);
        }
        else 
        {
            buzzer.write(0.15f);
            save_imu_samples(imu_samples_buf);
            buzzer.write(0.0f);
        }
    }
}

