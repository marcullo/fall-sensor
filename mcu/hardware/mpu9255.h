/* Note: 
 *     every configuration struct (which will be called 'tuple') must constist 
 *     of 2 bytes (register address - 1B and bit fields related to it - 1B)!
 */
#ifndef MPU9255_H_
#define MPU9255_H_

#include <stdint.h>
#include "mpu9255_register_map.h"

#define MPU9255_ADDRESS         0x68
#define MPU9255_WHO_AM_I_ID     0x73

struct MPU_XG_Offset_H {
    const uint8_t ADDRESS       : 8;
    uint8_t xg_offs_usr_h       : 8;
};

struct MPU_XG_Offset_L {
    const uint8_t ADDRESS       : 8;
    uint8_t xg_offs_usr_l       : 8;
};

struct MPU_YG_Offset_H {
    const uint8_t ADDRESS       : 8;
    uint8_t yg_offs_usr_h       : 8;
};

struct MPU_YG_Offset_L {
    const uint8_t ADDRESS       : 8;
    uint8_t yg_offs_usr_l       : 8;
};

struct MPU_ZG_Offset_H {
    const uint8_t ADDRESS       : 8;
    uint8_t zg_offs_usr_h       : 8;
};

struct MPU_ZG_Offset_L {
    const uint8_t ADDRESS       : 8;
    uint8_t zg_offs_usr_l       : 8;
};

struct MPU_Smplrt_Div {
    uint8_t ADDRESS             : 8;
    uint8_t smplrt_div          : 8;
};

struct MPU_Config {
    uint8_t ADDRESS             : 8;
    uint8_t dlpf_cfg            : 3;
    uint8_t ext_sync_set        : 3;
    uint8_t fifo_mode           : 1;
    uint8_t RESERVED0           : 1;
};

struct MPU_Gyro_Config {
    uint8_t ADDRESS             : 8;
    uint8_t fchoice_b           : 2;
    uint8_t RESERVED0           : 1;
    uint8_t gyro_fs_sel         : 2;
    uint8_t zgyro_cten          : 1;
    uint8_t ygyro_cten          : 1;
    uint8_t xgyro_cten          : 1;
};

struct MPU_Accel_Config {
    uint8_t ADDRESS             : 8;
    uint8_t RESERVED0           : 3;
    uint8_t accel_fs_sel        : 2;
    uint8_t az_st_en            : 1;
    uint8_t ay_st_en            : 1;
    uint8_t ax_st_en            : 1;
};

struct MPU_Accel_Config2 {
    uint8_t ADDRESS             : 8;
    uint8_t a_dlpfcfg           : 3;
    uint8_t accel_fchoice_b     : 1;
    uint8_t RESERVED0           : 4;
};

struct MPU_Fifo_En {
    uint8_t ADDRESS             : 8;
    uint8_t slv_0               : 1;
    uint8_t slv_1               : 1;
    uint8_t slv_2               : 1;
    uint8_t accel               : 1;
    uint8_t gyro_zout           : 1;
    uint8_t gyro_yout           : 1;
    uint8_t gyro_xout           : 1;
    uint8_t temp_out            : 1;
};

struct MPU_Int_Pin_Cfg {
    uint8_t ADDRESS             : 8;
    uint8_t RESERVED0           : 1;
    uint8_t bypass_en           : 1;
    uint8_t fsync_int_mode_en   : 1;
    uint8_t actl_fsync          : 1;
    uint8_t int_anyrd_2clear    : 1;
    uint8_t latch_int_en        : 1;
    uint8_t open                : 1;
    uint8_t actl                : 1;
};

struct MPU_Int_Enable {
    uint8_t ADDRESS             : 8;
    uint8_t raw_rdy_en          : 1;
    uint8_t RESERVED0           : 1;
    uint8_t RESERVED1           : 1;
    uint8_t fsync_int_en        : 1;
    uint8_t fifo_overflow_en    : 1;
    uint8_t RESERVED2           : 1;
    uint8_t WOM_EN              : 1;
    uint8_t RESERVED3           : 1;
};

struct MPU_Int_Status {
    uint8_t ADDRESS             : 8;
    uint8_t raw_data_rdy_int    : 1;
    uint8_t RESERVED0           : 1;
    uint8_t RESERVED1           : 1;
    uint8_t fsync_int           : 1;
    uint8_t fifo_overflow_int   : 1;
    uint8_t RESERVED2           : 1;
    uint8_t wom_int             : 1;
    uint8_t RESERVED3           : 1;
};

struct MPU_Accel_Out {          /* addr + 48b */
    uint8_t ADDRESS             : 8;
    uint8_t accel_xout_h        : 8;
    uint8_t accel_xout_l        : 8;
    uint8_t accel_yout_h        : 8;
    uint8_t accel_yout_l        : 8;
    uint8_t accel_zout_h        : 8;
    uint8_t accel_zout_l        : 8;
};

struct MPU_Temp_Out {
    uint8_t ADDRESS             : 8;
    uint8_t temp_xout_h         : 8;
    uint8_t temp_xout_l         : 8;
};

struct MPU_Gyro_Out {           /* addr + 48b */
    uint8_t ADDRESS             : 8;
    uint8_t gyro_xout_h         : 8;
    uint8_t gyro_xout_l         : 8;
    uint8_t gyro_yout_h         : 8;
    uint8_t gyro_yout_l         : 8;
    uint8_t gyro_zout_h         : 8;
    uint8_t gyro_zout_l         : 8;
};

struct MPU_User_Ctrl {
    uint8_t ADDRESS             : 8;
    uint8_t sig_cond_rst        : 1;
    uint8_t i2c_mst_rst         : 1;
    uint8_t fifo_rst            : 1;
    uint8_t RESERVED0           : 1;
    uint8_t i2c_if_dis          : 1;
    uint8_t i2c_mst_en          : 1;
    uint8_t fifo_en             : 1;
    uint8_t RESERVED1           : 1;
};

struct MPU_Pwr_Mgmt_1 {
    uint8_t ADDRESS             : 8;
    uint8_t clksel              : 3;
    uint8_t pd_ptat             : 1;
    uint8_t gyro_standby        : 1;
    uint8_t cycle               : 1;
    uint8_t sleep               : 1;
    uint8_t h_reset             : 1;
};

struct MPU_Pwr_Mgmt_2 {
    uint8_t ADDRESS             : 8;
    uint8_t disable_zg          : 1;
    uint8_t disable_yg          : 1;
    uint8_t disable_xg          : 1;
    uint8_t disable_za          : 1;
    uint8_t disable_ya          : 1;
    uint8_t disable_xa          : 1;
    uint8_t RESERVED0           : 2;
};

struct MPU_Fifo_Count_H {
    uint8_t ADDRESS             : 8;
    uint8_t fifo_cnt_h          : 5;
    uint8_t RESERVED0           : 3;
};

struct MPU_Fifo_Count_L {
    uint8_t ADDRESS             : 8;
    uint8_t fifo_cnt_l          : 8;
};

struct MPU_Who_Am_I {
    uint8_t ADDRESS             : 8;
    uint8_t whoami              : 8;
};

struct MPU_XA_Offset_H {
    uint8_t ADDRESS             : 8;
    uint8_t xg_offs_usr_h       : 8;
};

struct MPU_XA_Offset_L {
    uint8_t ADDRESS             : 8;
    uint8_t xg_offs_usr_l       : 8;
};

struct MPU_YA_Offset_H {
    uint8_t ADDRESS             : 8;
    uint8_t yg_offs_usr_h       : 8;
};

struct MPU_YA_Offset_L {
    uint8_t ADDRESS             : 8;
    uint8_t yg_offs_usr_l       : 8;
};

struct MPU_ZA_Offset_H {
    uint8_t ADDRESS             : 8;
    uint8_t zg_offs_usr_h       : 8;
};

struct MPU_ZA_Offset_L {
    uint8_t ADDRESS             : 8;
    uint8_t zg_offs_usr_l       : 8;
};

/*----------------------------------------------------------------------------*/

void mpu9255_set_transfer_frequency(uint32_t frequency);
void mpu9255_read_reg(uint8_t reg, uint8_t* value);
void mpu9255_write_reg(uint8_t reg, uint8_t val);
void mpu9255_write_tuple(uint8_t* bytes_tuple);
void mpu9255_read_regs(uint8_t first_reg, uint8_t regs_nr, uint8_t* data);
void mpu9255_write_regs(uint8_t first_reg, const uint8_t* data, uint8_t regs_nr);

#endif /* MPU9255_H_ */
