/* Example of use:
 * 1. Prepare struct Sensor_Configuration:
       struct Sensor_Configuration sensor_cfg = {
           .accel_fs_range     = ACCEL_FS_2G,
           .gyro_fs_range      = GYRO_FS_250DPS,
           .odr                = ODR_50HZ,
           .adlpf_cfg          = ADLPF_CFG_10HZ,
           .gdlpf_cfg          = GDLPF_CFG_10HZ,
           .int_pin_mode       = INT_PIN_OPEN_DRAIN_FALLING_EDGE,
           .int_mode           = INTERRUPT_MODE_DATA_RDY,
       };
 * 2. Configure sensor:
       if (sensor_is_valid_configuration(&sensor_cfg))
           sensor_configure(&sensor_cfg);
 * 3. Acquire sample
       struct ImuSample imu_sample;
       if (sensor_is_new_data_ready())
           sensor_acquire_sample(&imu_sample);
 */
#ifndef SENSOR_H_
#define SENSOR_H_

#include "imu_buffer.h"

#define SENSOR_RESOLUTION               16
#define SENSOR_DEFAULT_ACCEL_FS_RANGE   ACCEL_FS_8G
#define SENSOR_DEFAULT_GYRO_FS_RANGE    GYRO_FS_1000DPS
#define SENSOR_DEFAULT_ODR              ODR_100HZ
#define SENSOR_DEFAULT_ADLPF_CFG        ADLPF_CFG_5HZ
#define SENSOR_DEFAULT_GDLPF_CFG        GDLPF_CFG_5HZ
#define SENSOR_DEFAULT_INT_PIN_MODE     INT_PIN_OPEN_DRAIN_FALLING_EDGE
#define SENSOR_DEFAULT_INT_MODE         INTERRUPT_MODE_DATA_RDY

enum Sensor_Accel_Full_Scale_Range {
    ACCEL_FS_2G,
    ACCEL_FS_4G,
    ACCEL_FS_8G,
    ACCEL_FS_16G,
    ACCEL_FS_TOP  
};

enum Sensor_Gyro_Full_Scale_Range {
    GYRO_FS_250DPS,
    GYRO_FS_500DPS,
    GYRO_FS_1000DPS,
    GYRO_FS_2000DPS,
    GYRO_FS_TOP
};

enum Sensor_Output_Data_Rate {
    ODR_10HZ,
    ODR_20HZ,
    ODR_40HZ,
    ODR_50HZ,
    ODR_100HZ,
    ODR_200HZ,
    ODR_500HZ,
    ODR_1000HZ,
    ODR_TOP
};

enum Sensor_Accel_Digital_Lowpass_Config {
    ADLPF_CFG_5HZ,
    ADLPF_CFG_10HZ,
    ADLPF_CFG_20HZ,
    ADLPF_CFG_41HZ,
    ADLPF_CFG_92HZ,
    ADLPF_CFG_184HZ,
    ADLPF_CFG_460HZ,
    ADLPF_CFG_TOP
};

enum Sensor_Gyro_Digital_Lowpass_Config {
    GDLPF_CFG_5HZ,
    GDLPF_CFG_10HZ,
    GDLPF_CFG_20HZ,
    GDLPF_CFG_41HZ,
    GDLPF_CFG_92HZ,
    GDLPF_CFG_184HZ,
    GDLPF_CFG_TOP
};

enum Sensor_Interrupt_Pin_Mode {
    INT_PIN_OPEN_DRAIN_FALLING_EDGE,
    INT_PIN_MODE_TOP
};

enum Sensor_Interrupt_Mode {
    INTERRUPT_MODE_DATA_RDY,
    INTERRUPT_MODE_TOP
};

/* is related to function: sensor_get_active_configuration */
struct Sensor_Configuration {
    enum Sensor_Accel_Full_Scale_Range accel_fs_range;
    enum Sensor_Gyro_Full_Scale_Range gyro_fs_range;
    enum Sensor_Output_Data_Rate odr;
    enum Sensor_Accel_Digital_Lowpass_Config adlpf_cfg;
    enum Sensor_Gyro_Digital_Lowpass_Config gdlpf_cfg;
    enum Sensor_Interrupt_Pin_Mode int_pin_mode;
    enum Sensor_Interrupt_Mode int_mode;
    uint32_t resolution;
};

#define SIZEOF_REGS_CONFIG  (2 * sizeof(struct Regs_Config)/sizeof(struct MPU_Pwr_Mgmt_1))
struct regs_config;

void sensor_init();
bool sensor_is_valid_configuration(struct Sensor_Configuration* config);
void sensor_get_active_configuration(struct Sensor_Configuration* dest);
void sensor_set_default_configuration();
void sensor_configure(struct Sensor_Configuration* config);
void sensor_enable_data_ready_interrupt();
void sensor_disable_data_ready_interrupt();
bool sensor_is_new_data_ready();
void sensor_acquire_sample_to_buf(struct ImuBuffer* buf);
void sensor_acquire_sample(struct ImuSample* sample);

#endif /* SENSOR_H_ */
