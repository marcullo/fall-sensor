#ifndef MPU9255_REGISTER_MAP_H_
#define MPU9255_REGISTER_MAP_H_

#define X_OFFS_USR_H                    0x13
#define X_OFFS_USR_L                    0x14
#define Y_OFFS_USR_H                    0x15
#define Y_OFFS_USR_L                    0x16
#define Z_OFFS_USR_H                    0x17
#define Z_OFFS_USR_L                    0x18

#define SMPLRT_DIV                      0x19
#define CONFIG                          0x1A
#define GYRO_CONFIG                     0x1B
#define ACCEL_CONFIG                    0x1C
#define ACCEL_CONFIG2                   0x1D

#define FIFO_ENABLE                     0x23

#define ACCEL_XOUT_H                    0x3B
#define ACCEL_XOUT_L                    0x3C
#define ACCEL_YOUT_H                    0x3D
#define ACCEL_YOUT_L                    0x3E
#define ACCEL_ZOUT_H                    0x3F
#define ACCEL_ZOUT_L                    0x40

#define GYRO_XOUT_H                     0x43
#define GYRO_XOUT_L                     0x44
#define GYRO_YOUT_H                     0x45
#define GYRO_YOUT_L                     0x46
#define GYRO_ZOUT_H                     0x47
#define GYRO_ZOUT_L                     0x48

#define PWR_MGMT_1                      0x6B
#define WHO_AM_I                        0x75

#define WHO_AM_I_IDENTITY               0x73

#define XA_OFFS_H                       0x77
#define XA_OFFS_L                       0x78
#define YA_OFFS_H                       0x79
#define YA_OFFS_L                       0x7A
#define ZA_OFFS_H                       0x7B
#define ZA_OFFS_L                       0x7C

#define CONFIG_FIFO_MODE                (uint8_t)0x40
#define CONFIG_FSYNC_DISABLED           (uint8_t)0x00
#define CONFIG_FSYNC_TEMP_OUT_L         (uint8_t)0x08
#define CONFIG_FSYNC_GYRO_XOUT_L        (uint8_t)0x10
#define CONFIG_FSYNC_GYRO_YOUT_L        (uint8_t)0x18
#define CONFIG_FSYNC_GYRO_ZOUT_L        (uint8_t)0x20
#define CONFIG_FSYNC_ACCEL_XOUT_L       (uint8_t)0x28
#define CONFIG_FSYNC_ACCEL_YOUT_L       (uint8_t)0x40
#define CONFIG_FSYNC_ACCEL_ZOUT_L       (uint8_t)0x48
#define CONFIG_DLPF_CFG_0               (uint8_t)0x00
#define CONFIG_DLPF_CFG_1               (uint8_t)0x01
#define CONFIG_DLPF_CFG_2               (uint8_t)0x02
#define CONFIG_DLPF_CFG_3               (uint8_t)0x03
#define CONFIG_DLPF_CFG_4               (uint8_t)0x04
#define CONFIG_DLPF_CFG_5               (uint8_t)0x05
#define CONFIG_DLPF_CFG_6               (uint8_t)0x06
#define CONFIG_DLPF_CFG_7               (uint8_t)0x07

#define GYRO_CONFIG_XGYRO_CTEN          (uint8_t)0x80
#define GYRO_CONFIG_YGYRO_CTEN          (uint8_t)0x40
#define GYRO_CONFIG_ZGYRO_CTEN          (uint8_t)0x20
#define GYRO_CONFIG_FULL_SCALE_250DPS   (uint8_t)0x00
#define GYRO_CONFIG_FULL_SCALE_500DPS   (uint8_t)0x08
#define GYRO_CONFIG_FULL_SCALE_1000DPS  (uint8_t)0x10
#define GYRO_CONFIG_FULL_SCALE_2000DPS  (uint8_t)0x18
#define GYRO_CONFIG_FCHOICE_B_0         (uint8_t)0x00
#define GYRO_CONFIG_FCHOICE_B_1         (uint8_t)0x01

#define ACCEL_CONFIG_AX_ST_EN           (uint8_t)0x80
#define ACCEL_CONFIG_AY_ST_EN           (uint8_t)0x40
#define ACCEL_CONFIG_AZ_ST_EN           (uint8_t)0x20
#define ACCEL_CONFIG_FULL_SCALE_2G      (uint8_t)0x00
#define ACCEL_CONFIG_FULL_SCALE_4G      (uint8_t)0x08
#define ACCEL_CONFIG_FULL_SCALE_8G      (uint8_t)0x10
#define ACCEL_CONFIG_FULL_SCALE_16G     (uint8_t)0x18

#define ACCEL_CONFIG2_FCHOICE_B_0       (uint8_t)0x00
#define ACCEL_CONFIG2_FCHOICE_B_1       (uint8_t)0x08
#define ACCEL_CONFIG2_A_DLPFCFG_0       (uint8_t)0x00
#define ACCEL_CONFIG2_A_DLPFCFG_1       (uint8_t)0x01
#define ACCEL_CONFIG2_A_DLPFCFG_2       (uint8_t)0x02
#define ACCEL_CONFIG2_A_DLPFCFG_3       (uint8_t)0x03
#define ACCEL_CONFIG2_A_DLPFCFG_4       (uint8_t)0x04
#define ACCEL_CONFIG2_A_DLPFCFG_5       (uint8_t)0x05
#define ACCEL_CONFIG2_A_DLPFCFG_6       (uint8_t)0x06
#define ACCEL_CONFIG2_A_DLPFCFG_7       (uint8_t)0x07

#define PWR_MGMT_1_RST                  (uint8_t)0x00
#define PWR_MGMT_1_H_RESET              (uint8_t)0x80
#define PWR_MGMT_1_SLEEP                (uint8_t)0x40
#define PWR_MGMT_1_CYCLE                (uint8_t)0x20
#define PWR_MGMT_1_GYRO_STANDBY         (uint8_t)0x10
#define PWR_MGMT_1_PD_PTAT              (uint8_t)0x08


#endif /* MPU9255_REGISTER_MAP_H_ */
