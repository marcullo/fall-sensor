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
    
    if(imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, &start_reg, sizeof(start_reg)))
        process_error();
        
    if(imu_i2c.read(ACC_GYRO_ADDRESS_7B_READ, rx_data, 6))
        process_error();
}

static inline void i2c_read_reg(uint8_t reg, uint8_t* value)
{
    if (value == NULL)
        return;
    
    char rx_reg = reg;
    char* rx_data = (char*)value;
    
    if(imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, &rx_reg, sizeof(rx_reg)))
        process_error();
        
    if(imu_i2c.read(ACC_GYRO_ADDRESS_7B_READ, rx_data, 1))
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
            {PWR_MGMT_1, PWR_MGMT_1_RST},
            {SMPLRT_DIV, 0x00},
            {CONFIG, CONFIG_FSYNC_DISABLED | CONFIG_DLPF_CFG_2},
            {GYRO_CONFIG, GYRO_CONFIG_FULL_SCALE_1000DPS},
            {ACCEL_CONFIG, ACCEL_CONFIG_FULL_SCALE_8G},
            {ACCEL_CONFIG2, ACCEL_CONFIG2_FCHOICE_B_0 | ACCEL_CONFIG2_A_DLPFCFG_2}
    };
    
    for (uint32_t i = 0; i < sizeof(init_table) / sizeof(init_table[0]); i++) {
        i2c_write_reg(init_table[i][0], init_table[i][1]);
    }
    
    wait(0.05);
}

bool mpu9255_is_connected()
{
    char identity = 0x00;
    char who_am_i_reg = WHO_AM_I;
    
    if(imu_i2c.write(ACC_GYRO_ADDRESS_7B_WRITE, &who_am_i_reg, sizeof(who_am_i_reg)))
        process_error();
        
    if(imu_i2c.read(ACC_GYRO_ADDRESS_7B_READ, &identity, sizeof(identity)))
        process_error();
        
    return identity == WHO_AM_I_IDENTITY;
}

void mpu9255_accel_read_data_regs(uint8_t* data)
{
    i2c_read_regs(ACCEL_XOUT_H, 6, data);
}

void mpu9255_gyro_read_data_regs(uint8_t* data)
{
    i2c_read_regs(GYRO_XOUT_H, 6, data);
}