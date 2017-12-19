/* Based on: MPU-9255 Register Map and Descriptions Revision 1.0 (InvenSense) 
 * Note:
 *     the reset value is 0x00 for all registers other than:
           - register 107=0x6B Power Management 1   (0x01)
           - register 117=0x75 WHO Am I             (0x73)
 */
#ifndef MPU9255_REGISTER_MAP_H_
#define MPU9255_REGISTER_MAP_H_

/* Registers 0 to 2 – Gyroscope Self-Test Registers */
#define SELF_TEST_X_GYRO                0x00 /* R/W RST:0x00 */
#define SELF_TEST_Y_GYRO                0x01 /* R/W RST:0x00 */
#define SELF_TEST_Z_GYRO                0x02 /* R/W RST:0x00 */
/* Registers 13 to 15 – Accelerometer Self-Test Registers */
#define SELF_TEST_X_ACCEL               0x0D /* R/W RST:0x00 */
#define SELF_TEST_Y_ACCEL               0x0E /* R/W RST:0x00 */
#define SELF_TEST_Z_ACCEL               0x0F /* R/W RST:0x00 */
/* Registers 19 to 24 – Gyro Offset Registers */
#define XG_OFFSET_H                     0x13 /* R/W RST:0x00 */
#define XG_OFFSET_L                     0x14 /* R/W RST:0x00 */
#define YG_OFFSET_H                     0x15 /* R/W RST:0x00 */
#define YG_OFFSET_L                     0x16 /* R/W RST:0x00 */
#define ZG_OFFSET_H                     0x17 /* R/W RST:0x00 */
#define ZG_OFFSET_L                     0x18 /* R/W RST:0x00 */
/* Register 25 – Sample Rate Divider */
#define SMPLRT_DIV                      0x19 /* R/W RST:0x00 */
/* Register 26 – Configuration */
#define CONFIG                          0x1A /* R/W RST:0x00 */
/* Register 27 – Gyroscope Configuration */
#define GYRO_CONFIG                     0x1B /* R/W RST:0x00 */
/* Register 28 – Accelerometer Configuration */
#define ACCEL_CONFIG                    0x1C /* R/W RST:0x00 */
/* Register 29 – Accelerometer Configuration 2 */
#define ACCEL_CONFIG2                   0x1D /* R/W RST:0x00 */
/* Register 30 – Low Power Accelerometer ODR Control */
#define LP_ACCEL_ODR                    0x1E /* R/W RST:0x00 */
/* Register 31 – Wake-on Motion Threshold */
#define WOM_THR                         0x1F /* R/W RST:0x00 */
/* Register 35 – FIFO Enable */
#define FIFO_EN                         0x23 /* R/W RST:0x00 */
/* Register 36 – I2C Master Control */
#define I2C_MST_CTRL                    0x24 /* R/W RST:0x00 */
/* Registers 37 to 39 – I2C Slave 0 Control */
#define I2C_SLV0_ADDR                   0x25 /* R/W RST:0x00 */
#define I2C_SLV0_REG                    0x26 /* R/W RST:0x00 */
#define I2C_SLV0_CTRL                   0x27 /* R/W RST:0x00 */
/* Registers 40 to 42 – I2C Slave 1 Control */
#define I2C_SLV1_ADDR                   0x28 /* R/W RST:0x00 */
#define I2C_SLV1_REG                    0x29 /* R/W RST:0x00 */
#define I2C_SLV1_CTRL                   0x2A /* R/W RST:0x00 */
/* Registers 43 to 45 – I2C Slave 2 Control */
#define I2C_SLV2_ADDR                   0x2B /* R/W RST:0x00 */
#define I2C_SLV2_REG                    0x2C /* R/W RST:0x00 */
#define I2C_SLV2_CTRL                   0x2D /* R/W RST:0x00 */
/* Registers 46 to 48 – I2C Slave 3 Control */
#define I2C_SLV3_ADDR                   0x2E /* R/W RST:0x00 */
#define I2C_SLV3_REG                    0x2F /* R/W RST:0x00 */
#define I2C_SLV3_CTRL                   0x30 /* R/W RST:0x00 */
/* Registers 49 to 43 – I2C Slave 4 Control */
#define I2C_SLV4_ADDR                   0x31 /* R/W RST:0x00 */
#define I2C_SLV4_REG                    0x32 /* R/W RST:0x00 */
#define I2C_SLV4_DO                     0x33 /* R/W RST:0x00 */
#define I2C_SLV4_CTRL                   0x34 /* R/W RST:0x00 */
#define I2C_SLV4_DI                     0x35 /*  R  RST:0x00*/
/* Register 54 – I2C Master Status */
#define I2C_MST_STATUS                  Ox36 /*  R  RST:0x00*/
/* Register 55 – INT Pin / Bypass Enable Configuration */
#define INT_PIN_CFG                     0x37 /* R/W RST:0x00*/
/* Register 56 – Interrupt Enable */
#define INT_ENABLE                      0x38 /* R/W RST:0x00*/
/* Register 58 – Interrupt Status */
#define INT_STATUS                      0x3A /*  R  RST:0x00*/
/*  Registers 59 to 64 – Accelerometer Measurements */
#define ACCEL_XOUT_H                    0x3B /*  R  RST:0x00 (if sensor disabled) */
#define ACCEL_XOUT_L                    0x3C /*  R  RST:0x00 (if sensor disabled) */
#define ACCEL_YOUT_H                    0x3D /*  R  RST:0x00 (if sensor disabled) */
#define ACCEL_YOUT_L                    0x3E /*  R  RST:0x00 (if sensor disabled) */
#define ACCEL_ZOUT_H                    0x3F /*  R  RST:0x00 (if sensor disabled) */
#define ACCEL_ZOUT_L                    0x40 /*  R  RST:0x00 (if sensor disabled) */
/* Registers 65 and 66 – Temperature Measurement */
#define TEMP_OUT_H                      0x41 /*  R  RST:0x00 (if sensor disabled) */
#define TEMP_OUT_L                      0x42 /*  R  RST:0x00 (if sensor disabled) */
/* Registers 67 to 72 – Gyroscope Measurements */
#define GYRO_XOUT_H                     0x43 /*  R  RST:0x00 (if sensor disabled) */
#define GYRO_XOUT_L                     0x44 /*  R  RST:0x00 (if sensor disabled) */
#define GYRO_YOUT_H                     0x45 /*  R  RST:0x00 (if sensor disabled) */
#define GYRO_YOUT_L                     0x46 /*  R  RST:0x00 (if sensor disabled) */
#define GYRO_ZOUT_H                     0x47 /*  R  RST:0x00 (if sensor disabled) */
#define GYRO_ZOUT_L                     0x48 /*  R  RST:0x00 (if sensor disabled) */
/* Registers 73 to 96 – External Sensor Data */
#define EXT_SENS_DATA_00                0x49 /*  R  RST:0x00 */
#define EXT_SENS_DATA_01                0x4A /*  R  RST:0x00 */
#define EXT_SENS_DATA_02                0x4B /*  R  RST:0x00 */
#define EXT_SENS_DATA_03                0x4C /*  R  RST:0x00 */
#define EXT_SENS_DATA_04                0x4D /*  R  RST:0x00 */
#define EXT_SENS_DATA_05                0x4E /*  R  RST:0x00 */
#define EXT_SENS_DATA_06                0x4F /*  R  RST:0x00 */
#define EXT_SENS_DATA_07                0x50 /*  R  RST:0x00 */
#define EXT_SENS_DATA_08                0x51 /*  R  RST:0x00 */
#define EXT_SENS_DATA_09                0x52 /*  R  RST:0x00 */
#define EXT_SENS_DATA_10                0x53 /*  R  RST:0x00 */
#define EXT_SENS_DATA_11                0x54 /*  R  RST:0x00 */
#define EXT_SENS_DATA_12                0x55 /*  R  RST:0x00 */
#define EXT_SENS_DATA_13                0x56 /*  R  RST:0x00 */
#define EXT_SENS_DATA_14                0x57 /*  R  RST:0x00 */
#define EXT_SENS_DATA_15                0x58 /*  R  RST:0x00 */
#define EXT_SENS_DATA_16                0x59 /*  R  RST:0x00 */
#define EXT_SENS_DATA_17                0x5A /*  R  RST:0x00 */
#define EXT_SENS_DATA_18                0x5B /*  R  RST:0x00 */
#define EXT_SENS_DATA_19                0x5C /*  R  RST:0x00 */
#define EXT_SENS_DATA_20                0x5D /*  R  RST:0x00 */
#define EXT_SENS_DATA_21                0x5E /*  R  RST:0x00 */
#define EXT_SENS_DATA_22                0x5F /*  R  RST:0x00 */
#define EXT_SENS_DATA_23                0x60 /*  R  RST:0x00 */
/* Register 99 – I2C Slave 0 Data Out */
#define I2C_SLV0_DO                     0x63 /* R/W RST:0x00 */
/* Register 100 – I2C Slave 1 Data Out */
#define I2C_SLV1_DO                     0x64 /* R/W RST:0x00 */
/* Register 101 – I2C Slave 2 Data Out */
#define I2C_SLV2_DO                     0x65 /* R/W RST:0x00 */
/* Register 102 – I2C Slave 3 Data Out */
#define I2C_SLV3_DO                     0x66 /* R/W RST:0x00 */
/* Register 103 – I2C Master Delay Control */
#define I2C_MST_DELAY_CTRL              0x67 /* R/W RST:0x00 */
/* Register 104 – Signal Path Reset */
#define SIGNAL_PATH_RESET               0x68 /* R/W RST:0x00 */
/* Register 105 – Accelerometer Interrupt Control */
#define MOST_DETECT_CTRL                0x69 /* R/W RST:0x00 */
/* Register 106 – User Control */
#define USER_CTRL                       0x6A /* R/W RST:0x00 */
/* Register 107 – Power Management 1 */
#define PWR_MGMT_1                      0x6B /* R/W RST:0x01(depends on PU_SLEEP_MODE bit)*/
/* Register 108 – Power Management 2 */
#define PWR_MGMT_2                      0x6C /* R/W RST:0x00 */
/* Register 114 and 115 – FIFO Count Registers */
#define FIFO_COUNTH                     0x72 /*  R  RST:0x00 */
#define FIFO_COUNTL                     0x73 /*  R  RST:0x00 */
/* Register 116 – FIFO Read Write */
#define FIFO_R_W                        0x74 /* R/W RST:0x00 */
/* Register 117 – Who Am I */
#define WHO_AM_I                        0x75 /*  R  RST:0x73 */
/* Registers 119, 120, 122, 123, 125, 126 Accelerometer Offset Registers */
#define XA_OFFSET_H                     0x77 /* R/W RST:0x00 */
#define XA_OFFSET_L                     0x78 /* R/W RST:0x00 */
#define YA_OFFSET_H                     0x7A /* R/W RST:0x00 */
#define YA_OFFSET_L                     0x7B /* R/W RST:0x00 */
#define ZA_OFFSET_H                     0x7D /* R/W RST:0x00 */
#define ZA_OFFSET_L                     0x7E /* R/W RST:0x00 */

#endif /* MPU9255_REGISTER_MAP_H_ */
