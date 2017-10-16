#include "mbed.h" /* Release 150 */
#include "sdk/hardware/mpu9255.h"

#define MODE_DISPLAY 0
#define MODE_SAVE 1

DigitalOut successLed(LED1);
Serial pc(SERIAL_TX, SERIAL_RX);

int main()
{
    pc.baud(921600);
    mpu9255_init();
    
    uint8_t data_frame[13];
    data_frame[12] = '\0';
    
    uint8_t app_mode = 0;    
    while(!pc.readable())
        ;
    app_mode = pc.getc() - '0';
    
    switch(app_mode)
    {
        case MODE_DISPLAY:
            while(1)
            {
                mpu9255_accel_read_data_regs(data_frame);
                mpu9255_gyro_read_data_regs(data_frame+6);
                
                pc.printf("a%db%dc%d", 
                        (int16_t)((data_frame[0] << 8) + data_frame[1]),
                        (int16_t)((data_frame[2] << 8) + data_frame[3]),
                        (int16_t)((data_frame[4] << 8) + data_frame[5]));
                
                pc.printf("d%de%df%d", 
                        (int16_t)((data_frame[6] << 8) + data_frame[7]),
                        (int16_t)((data_frame[8] << 8) + data_frame[9]),
                        (int16_t)((data_frame[10] << 8) + data_frame[11]));
                
                pc.printf("\r");
            }
            break;
            
        case MODE_SAVE:
            while(1)
            {
                mpu9255_accel_read_data_regs(data_frame);
                mpu9255_gyro_read_data_regs(data_frame+6);
                
                pc.printf("%d %d %d ", 
                        (int16_t)((data_frame[0] << 8) + data_frame[1]),
                        (int16_t)((data_frame[2] << 8) + data_frame[3]),
                        (int16_t)((data_frame[4] << 8) + data_frame[5]));
                
                pc.printf("%d %d %d", 
                        (int16_t)((data_frame[6] << 8) + data_frame[7]),
                        (int16_t)((data_frame[8] << 8) + data_frame[9]),
                        (int16_t)((data_frame[10] << 8) + data_frame[11]));
                
                pc.printf("\r");
            }
            break;
            
        default: 
            pc.printf("Invalid app mode!");
            while(1)
                ;
            break;
    }
}