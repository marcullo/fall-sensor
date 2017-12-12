#include "mpu9255.h"
#include "mbed.h"
#include "mpu9255_register_map.h"
#include <tools/error_handler.h>

#define ACC_GYRO_ADDRESS_7B 0xD0
#define ACC_GYRO_ADDRESS_7B_WRITE (ACC_GYRO_ADDRESS_7B | 1)
#define ACC_GYRO_ADDRESS_7B_READ (ACC_GYRO_ADDRESS_7B | 0)

static I2C imu_i2c(I2C_SDA, I2C_SCL);

//-----------------------------------------------------------------------------

static inline void i2c_read_regs(uint8_t first_reg, uint8_t regs_nr, uint8_t* data)
{
    if (regs_nr == 0)
        return;
    if (data == NULL)
        return;
        
    char start_reg = first_reg;
    char* rx_data = (char*)data; 
    
    imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, &start_reg, sizeof(start_reg), true);
    if(imu_i2c.read(ACC_GYRO_ADDRESS_7B_READ, rx_data, regs_nr))
        process_error();
}

static inline void i2c_read_reg(uint8_t reg, uint8_t* value)
{
    if (value == NULL)
        return;
    
    char rx_reg = reg;
    char* rx_data = (char*)value;
    
    imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, &rx_reg, 1, true);
    if (imu_i2c.read(ACC_GYRO_ADDRESS_7B_READ, rx_data, 1) != 0)
        process_error();
}

static inline void i2c_write_reg(uint8_t reg, uint8_t val)
{
    char tx_buf[2] = {
        reg, 
        val
    };
    
    if(imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, tx_buf, sizeof(tx_buf)))
        process_error();
}

//-----------------------------------------------------------------------------

void mpu9255_init()
{
    imu_i2c.frequency(400000);
    
    wait(0.05);
    
    if (!mpu9255_is_connected()) {
        process_error();
    }
    
    uint8_t init_table[][2] = {
            {PWR_MGMT_1, 0x00},
            {SMPLRT_DIV, 0x09},
            {CONFIG, 0x06},
            {GYRO_CONFIG, 0x10},
            {ACCEL_CONFIG, 0x10},
            {ACCEL_CONFIG2, 0x06},
            {INT_PIN_CFG, 0xD3},
            {INT_ENABLE, 0x01}
    };
    
    for (uint32_t i = 0; i < sizeof(init_table) / sizeof(init_table[0]); i++) {
        i2c_write_reg(init_table[i][0], init_table[i][1]);
    }
    
    wait(0.05);
}

bool mpu9255_is_connected()
{
    uint8_t identity = 0x00;   
    i2c_read_reg(WHO_AM_I, &identity);
    return identity == WHO_AM_I_IDENTITY;
}

void mpu9255_read_data(uint8_t* data)
{
    i2c_read_regs(ACCEL_XOUT_H, 14, data);
}
