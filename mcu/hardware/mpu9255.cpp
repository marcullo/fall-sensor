#include "mpu9255.h"
#include "mbed.h"
#include "pinout.h"
#include <tools/error_handler.h>

#define MPU9255_ADDRESS_WRITE   ((MPU9255_ADDRESS << 1) | 1)
#define MPU9255_ADDRESS_READ    ((MPU9255_ADDRESS << 1) | 0)

static I2C imu_i2c(MPU9255_I2C_SDA, MPU9255_I2C_SCL);

void mpu9255_set_transfer_frequency(uint32_t frequency)
{
    if (frequency < 10000 || frequency > 400000)
        return;
        
    imu_i2c.frequency(frequency);
}

void mpu9255_read_reg(uint8_t reg, uint8_t* value)
{
    if (!value)
        return;
    
    char rx_reg = reg;
    char* rx_data = (char*)value;
    
    imu_i2c.write(MPU9255_ADDRESS_WRITE, &rx_reg, 1, true);
    if (imu_i2c.read(MPU9255_ADDRESS_READ, rx_data, 1) != 0)
        process_error();
}

void mpu9255_write_reg(uint8_t reg, uint8_t val)
{
    char tx_buf[2] = {
        reg, 
        val
    };
    
    if(imu_i2c.write(MPU9255_ADDRESS_WRITE, tx_buf, sizeof(tx_buf)))
        process_error();
}

void mpu9255_write_tuple(uint8_t* bytes_tuple)
{
    if (!bytes_tuple)
        return;
        
    char* ctuple = (char*)bytes_tuple;
        
    if(imu_i2c.write(MPU9255_ADDRESS_WRITE, ctuple, 2))
        process_error();
}

void mpu9255_read_regs(uint8_t first_reg, uint8_t regs_nr, uint8_t* data)
{
    if (!data || regs_nr == 0)
        return;
        
    char start_reg = first_reg;
    char* rx_data = (char*)data; 
    
    imu_i2c.write(MPU9255_ADDRESS_WRITE, &start_reg, sizeof(start_reg), true);
    if(imu_i2c.read(MPU9255_ADDRESS_READ, rx_data, regs_nr))
        process_error();
}

void mpu9255_write_regs(uint8_t first_reg, const uint8_t* data, uint8_t regs_nr)
{
    if (!data || regs_nr == 0)
        return;
        
    char tx_buf[2];
        
    uint32_t reg_nr;
    for (reg_nr = first_reg; reg_nr < regs_nr; reg_nr++)
    {
        tx_buf[0] = reg_nr;
        tx_buf[1] = *data++;
        
        if(imu_i2c.write(MPU9255_ADDRESS_WRITE, tx_buf, sizeof(tx_buf)))
            process_error();
    }
}
