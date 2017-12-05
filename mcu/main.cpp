#include "mbed.h" /* Release 150 */
#include "SDFileSystem.h" /* 9 Sep 2016 */
#include "sdk/hardware/mpu9255.h"
#include "imu_buffer/imu_buffer.h"
#include "tools/error_handler.h"
#include "tools/global_def.h"
#include "command_decoder/command_decoder.h"
#include <stdlib.h>

#define DISC_NAME "sd"
#define PACKETS_PATH "/"DISC_NAME

#define IMU_SAMPLES_NR          5000
#define IMU_DEGREES_OF_FREEDOM  6
#define COLLECTING_FREQUENCY    1000
#define COLLECTING_TIME         (float)((float)1/(float)COLLECTING_FREQUENCY)

struct ImuSample imu_samples[IMU_SAMPLES_NR];
uint32_t collected_samples_nr;

#define HELLO_MESSAGE      "FSHELLO2017MARCULLO\r"
#define OK_MESSAGE         "OK\r"

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

void flush_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        return;
    
    buf_flush(buf);
}

void acquire_imu_samples(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();    
        
    uint8_t regs_read[14];
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
        
        mpu9255_read_data(regs_read);
        
        new_sample.ax = (uint16_t)(((uint16_t)regs_read[0] << 8) + regs_read[1]);
        new_sample.ay = (uint16_t)(((uint16_t)regs_read[2] << 8) + regs_read[3]);
        new_sample.az = (uint16_t)(((uint16_t)regs_read[4] << 8) + regs_read[5]);
        
        new_sample.gx = (uint16_t)(((uint16_t)regs_read[8] << 8) + regs_read[9]);
        new_sample.gy = (uint16_t)(((uint16_t)regs_read[10] << 8) + regs_read[11]);
        new_sample.gz = (uint16_t)(((uint16_t)regs_read[12] << 8) + regs_read[13]);
        
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

static uint32_t packet_nr = 0;

void save_imu_samples(struct ImuBuffer* buf)
{
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
            new_sample.ax,
            new_sample.ay,
            new_sample.az);
            
        fprintf(f, "%04x%04x%04x",
            new_sample.gx,
            new_sample.gy,
            new_sample.gz);
    }
    
    pc.printf("\r\nSaved!\r\n");
    
    fprintf(f, "\r\n");

    fclose(f);
    
    collected_samples_nr = 0;
    packet_nr++;
}

void read_number_of_packets()
{
    packet_nr = 0;
    
    DIR *dp;
    struct dirent *dirp;
    char file_path[30];
    
    dp = opendir(PACKETS_PATH);
    while((dirp = readdir(dp)) != NULL) 
    {
        sprintf(file_path, "%s/%s", PACKETS_PATH, dirp->d_name);
        FILE* f = fopen(file_path, "r");
        if (f) 
        {
            packet_nr++;
        }
        fclose(f);
    }
    pc.printf("PNUM: %d\r\n", packet_nr);
    wait(0.05);
}

void read_imu_samples(uint32_t packet_number, struct ImuBuffer* buf, uint32_t* read_samples_nr)
{
    if (!buf || !read_samples_nr)
        return;
    if (packet_number > packet_nr - 1)
        return;
        
    struct ImuSample new_sample;
    uint16_t* sample_elem = &(new_sample.ax);
        
    char fbuf[5];
    fbuf[4] = '\0';
    int read_cnt = 0;
    char file_path[20];
    
    sprintf(file_path, "/%s/%04x.dat", DISC_NAME, packet_number);
    
    FILE* f = fopen(file_path, "r");
    if (!f)
        process_error();

    read_cnt = fread(fbuf, 1, 2, f);
    fbuf[read_cnt] = '\0';
    if (strcmp(fbuf, "FS") != 0)
        process_error();
        
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    uint32_t samples_nr = strtoul(fbuf, NULL, 16);
    *read_samples_nr = samples_nr;
    
    if (samples_nr == 0)
    {
        fclose(f);
        return;
    }
    
    uint32_t i;
    for (i = 0; i < samples_nr * IMU_DEGREES_OF_FREEDOM; i++)
    {
        read_cnt = fread(fbuf, 1, 4, f);
        if (read_cnt < 4)
            break;
            
        *sample_elem = strtol(fbuf, NULL, 16);
        sample_elem++;
        
        if (i % IMU_DEGREES_OF_FREEDOM == (IMU_DEGREES_OF_FREEDOM - 1))
        {
            sample_elem = &(new_sample.ax);
            buf_replace_next(buf, &new_sample);
        }
    }
    if (read_cnt < 4)
        process_error();
        
    fclose(f);
}

void send_imu_samples(uint32_t packet_number, struct ImuBuffer* buf, uint32_t samples_nr)
{
    if (!buf)
        process_error();
     
    pc.printf("FS%04x%04x", packet_number, samples_nr);
    
    struct ImuSample new_sample;
    while(!buf_is_empty(buf))
    {
        buf_read_next(buf, &new_sample);
        
        pc.printf("%04x%04x%04x",
            new_sample.ax,
            new_sample.ay,
            new_sample.az);
            
        pc.printf("%04x%04x%04x",
            new_sample.gx,
            new_sample.gy,
            new_sample.gz);
    }
    
    pc.printf("\r");
}

void send_packets_nr()
{
    pc.printf("FS%04x\r", packet_nr);    
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

void respond_ok(void)
{
    pc.printf(OK_MESSAGE);
    wait(0.05);
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
            
        case FS_GOODBYE:
            respond_ok();
            return;
            
        case FS_RESET:
            respond_ok();
            NVIC_SystemReset();
            break;
            
        case FS_PACKETS_NR:
            send_packets_nr();
            break;
            
        case FS_FREQUENCY:
            send_frequency();
            break;
        
        case FS_PACKETS:
        {
            uint32_t samples_nr;
            uint32_t i;
            for (i = 0; i < packet_nr; i++)
            { 
                read_imu_samples(i, samples, &samples_nr);
                send_imu_samples(i, samples, samples_nr);
            }
        }
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
    
    while (1)
    {
        read_number_of_packets();
        
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
                break;
            }
            else 
            {
                buzzer.write(0.15f);
                save_imu_samples(imu_samples_buf);
                buzzer.write(0.0f);
            }
        }
    
        buzzer.write(0.25f);
        wait(1.0);
        buzzer.write(0.0f);
        flush_imu_samples(imu_samples_buf);
        process_pc_commands(imu_samples_buf);
    }
}

