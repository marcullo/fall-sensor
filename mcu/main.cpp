#include "mbed.h" /* Release 150 */
#include "sdk/hardware/mpu9255.h"
#include "tools/error_handler.h"

DigitalIn userButton(USER_BUTTON);
DigitalOut successLed(LED1);
Serial pc(PA_9, PA_10);
Ticker t;
volatile bool processing_next_data_allowed;

/* 8000 packets (acc x,y,z; gyro x,y,z 2B) */
uint8_t persistent_data[96000];

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

void record_persistent_data(uint8_t* data, uint32_t len)
{
    if (!data || !len)
        process_error();
        
    t.attach(&allow_processing_data, 0.001);
        
    uint32_t data_cnt = 0;
    while(data_cnt < len)
    {
        if(!processing_next_data_allowed)
            continue;
        
        mpu9255_accel_read_data_regs(data + data_cnt);
        data_cnt += 6;
        mpu9255_accel_read_data_regs(data + data_cnt);        
        data_cnt += 6;
        
        processing_next_data_allowed = false;
    }
    
    t.detach();
}

void send_persistent_packet(uint8_t* data, uint32_t len)
{
    if (!data || !len)
        process_error();
     
    uint32_t data_cnt = 0;
    while(data_cnt < len)
    {        
        pc.printf("%04x%04x%04x",
                (uint16_t)((data[data_cnt + 0] << 8) + data[data_cnt + 1]),   
                (uint16_t)((data[data_cnt + 2] << 8) + data[data_cnt + 3]),   
                (uint16_t)((data[data_cnt + 4] << 8) + data[data_cnt + 5]));  
        data_cnt += 6;
                
        pc.printf("%04x%04x%04x",
                (uint16_t)((data[data_cnt + 6] << 8) + data[data_cnt + 7]),   
                (uint16_t)((data[data_cnt + 8] << 8) + data[data_cnt + 9]),   
                (uint16_t)((data[data_cnt + 10] << 8) + data[data_cnt + 11]));
        data_cnt += 6;
        
        pc.printf("\r");
    }
}

int main()
{    
    pc.baud(115200);
    mpu9255_init();
        
    while(!isButtonPressed())
        ;
    
    record_persistent_data(persistent_data, sizeof(persistent_data));
    
    successLed.write(1);
    
    while(!isButtonPressed())
        ;
    send_persistent_packet(persistent_data, sizeof(persistent_data));
    
    successLed.write(0);
    
    while(1)
        ;
}

