#include "sensor.h"
#include "pinout.h"
#include "hardware/mpu9255.h"
#include "hardware/mpu9255_register_map.h"
#include "tools/error_handler.h"

#define SENSOR_WRITE_TUPLE(_bytes_tuple)  mpu9255_write_tuple((uint8_t*)_bytes_tuple);
#define RESOLUTION 16

static InterruptIn imu_int_pin(SENSOR_INTERRUPT_PIN);

struct Regs_Config {
    struct MPU_Pwr_Mgmt_1 pwr_mgmt_1;
    struct MPU_Smplrt_Div smplrt_div;
    struct MPU_Config config;
    struct MPU_Gyro_Config gyro_config;
    struct MPU_Accel_Config accel_config;
    struct MPU_Accel_Config2 accel_config2;
    struct MPU_Int_Pin_Cfg int_pin_cfg;
    struct MPU_Int_Enable int_enable; 
} regs_cfg = {
    .pwr_mgmt_1 = {
        .ADDRESS = PWR_MGMT_1,
    },
    .smplrt_div = {
        .ADDRESS = SMPLRT_DIV,
        .smplrt_div = 0x09,
    },
    .config = {
        .ADDRESS = CONFIG,
        .fifo_mode = 0,
        .ext_sync_set = 0,
        .dlpf_cfg = 6
    },
    .gyro_config = {
        .ADDRESS = GYRO_CONFIG,
        .gyro_fs_sel = 2
    },
    .accel_config = {
        .ADDRESS = ACCEL_CONFIG,
        .accel_fs_sel = 2
    },
    .accel_config2 = {
        .ADDRESS = ACCEL_CONFIG2,
        .a_dlpfcfg = 6
    },
    .int_pin_cfg = {
        .ADDRESS = INT_PIN_CFG,
        .actl = 1,
        .open = 1,
        .int_anyrd_2clear = 1,
        .bypass_en = 1
    },
    .int_enable = {
        .ADDRESS = INT_ENABLE,
        .raw_rdy_en = 1
    }
};

struct Sensor_Configuration sensor_config = {
    .accel_fs_range =   SENSOR_DEFAULT_ACCEL_FS_RANGE,
    .gyro_fs_range =    SENSOR_DEFAULT_GYRO_FS_RANGE,
    .odr =              SENSOR_DEFAULT_ODR,
    .adlpf_cfg =        SENSOR_DEFAULT_ADLPF_CFG,
    .gdlpf_cfg =        SENSOR_DEFAULT_GDLPF_CFG,
    .int_pin_mode =     SENSOR_DEFAULT_INT_PIN_MODE,
    .int_mode =         SENSOR_DEFAULT_INT_MODE,
    .resolution =       RESOLUTION
};

volatile bool new_data_ready;

static void imu_interrupt_handler()
{
    new_data_ready = true;
}

#define STABILIZATION_DELAY (0.05f)

static inline void wait_for_stabilization()
{
    wait(STABILIZATION_DELAY);
}

static void read_imu_data(uint8_t* data)
{
    mpu9255_read_regs(ACCEL_XOUT_H, 14, data);
}

static bool is_imu_connected()
{
    uint8_t identity = 0x00;
    mpu9255_read_reg(WHO_AM_I, &identity);
    return identity == MPU9255_WHO_AM_I_ID;
}

static void load_default_configuration()
{
    wait_for_stabilization();

    uint8_t* init_table = (uint8_t*) &regs_cfg;
    uint32_t i;
    for (i = 0; i < SIZEOF_REGS_CONFIG; i += 2) {
        mpu9255_write_reg(init_table[i], init_table[i+1]);
    }
    
    wait_for_stabilization();
}

static void configure_accel_fs_range(enum Sensor_Accel_Full_Scale_Range fs_range)
{
    if (fs_range >= ACCEL_FS_TOP)
        return;
        
    sensor_config.accel_fs_range = fs_range;    
    struct MPU_Accel_Config* accel_cfg = &regs_cfg.accel_config;
    accel_cfg->accel_fs_sel = fs_range;
    SENSOR_WRITE_TUPLE(accel_cfg);
}

static void configure_gyro_fs_range(enum Sensor_Gyro_Full_Scale_Range fs_range)
{
    if (fs_range >= GYRO_FS_TOP)
        return;
    
    sensor_config.gyro_fs_range = fs_range;
    struct MPU_Gyro_Config* gyro_cfg = &regs_cfg.gyro_config;
    gyro_cfg->gyro_fs_sel = fs_range;
    SENSOR_WRITE_TUPLE(gyro_cfg);
}

static void configure_odr(enum Sensor_Output_Data_Rate odr)
{        
    uint8_t smplrt_div_val;
    switch (odr)
    {
    case ODR_10HZ:
        smplrt_div_val = 0x63;
        break;
        
    case ODR_20HZ:
        smplrt_div_val = 0x31;
        break;
    
    case ODR_40HZ:
        smplrt_div_val = 0x18;
        break;
      
    case ODR_50HZ:
        smplrt_div_val = 0x13;
        break;
        
    case ODR_100HZ:
        smplrt_div_val = 0x09;
        break;
        
    case ODR_200HZ:
        smplrt_div_val = 0x04;
        break;
        
    case ODR_500HZ:
        smplrt_div_val = 0x01;
        break;
        
    case ODR_1000HZ:
        smplrt_div_val = 0x00;
        break;
        
    default:
        return;
    }
    
    sensor_config.odr = odr;
    struct MPU_Smplrt_Div* smplrt_div = &regs_cfg.smplrt_div;
    smplrt_div->smplrt_div = smplrt_div_val;
    SENSOR_WRITE_TUPLE(smplrt_div);
}

void configure_accel_digital_lowpass_filter(enum Sensor_Accel_Digital_Lowpass_Config dlpf_cfg)
{
    uint8_t dlpf_cfg_val;
    switch (dlpf_cfg)
    {
    case ADLPF_CFG_5HZ:
        dlpf_cfg_val = 6;
        break;
        
    case ADLPF_CFG_10HZ:
        dlpf_cfg_val = 5;
        break;
       
    case ADLPF_CFG_20HZ:
        dlpf_cfg_val = 4;
        break;
    
    case ADLPF_CFG_41HZ:
        dlpf_cfg_val = 3;
        break;
        
    case ADLPF_CFG_92HZ:
        dlpf_cfg_val = 2;
        break;
        
    case ADLPF_CFG_184HZ:
        dlpf_cfg_val = 1;
        break;
        
    case ADLPF_CFG_460HZ:
        dlpf_cfg_val = 0;
        break;
        
    default:
        return;
    }
    
    sensor_config.adlpf_cfg = dlpf_cfg;
    struct MPU_Accel_Config2* accel_config2 = &regs_cfg.accel_config2;
    accel_config2->a_dlpfcfg = dlpf_cfg_val;
    SENSOR_WRITE_TUPLE(accel_config2);    
}

void configure_gyro_digital_lowpass_filter(enum Sensor_Gyro_Digital_Lowpass_Config dlpf_cfg)
{
    uint8_t dlpf_cfg_val;
    switch (dlpf_cfg)
    {
    case GDLPF_CFG_5HZ:
        dlpf_cfg_val = 6;
        break;
        
    case GDLPF_CFG_10HZ:
        dlpf_cfg_val = 5;
        break;
       
    case GDLPF_CFG_20HZ:
        dlpf_cfg_val = 4;
        break;
    
    case GDLPF_CFG_41HZ:
        dlpf_cfg_val = 3;
        break;
        
    case GDLPF_CFG_92HZ:
        dlpf_cfg_val = 2;
        break;
        
    case GDLPF_CFG_184HZ:
        dlpf_cfg_val = 1;
        break;
        
    default:
        return;
    }
    
    sensor_config.gdlpf_cfg = dlpf_cfg;
    struct MPU_Config* mpu_config = &regs_cfg.config;
    mpu_config->dlpf_cfg = dlpf_cfg_val;
    SENSOR_WRITE_TUPLE(mpu_config);    
}

void configure_int_pin_mode(enum Sensor_Interrupt_Pin_Mode int_pin_mode)
{
    uint8_t falling_edge;
    uint8_t open_drain;
    
    switch (int_pin_mode)
    {
    case INTERRUPT_MODE_DATA_RDY:
        falling_edge = 1;
        open_drain = 1;
        break;
        
    default:
        return;
    }
    
    sensor_config.int_pin_mode = int_pin_mode;
    struct MPU_Int_Pin_Cfg* int_pin_cfg = &regs_cfg.int_pin_cfg;
    int_pin_cfg->actl = falling_edge;
    int_pin_cfg->open = open_drain;
    SENSOR_WRITE_TUPLE(int_pin_cfg);    
}

void configure_interrupt_mode(enum Sensor_Interrupt_Mode int_mode)
{
    uint8_t raw_rdy_en_val;
    switch (int_mode)
    {
    case INTERRUPT_MODE_DATA_RDY:
        raw_rdy_en_val = 1;
        break;
        
    default:
        return;
    }
    
    sensor_config.int_mode = int_mode;
    struct MPU_Int_Enable* int_enable = &regs_cfg.int_enable;
    int_enable->raw_rdy_en = raw_rdy_en_val;
    SENSOR_WRITE_TUPLE(int_enable);    
}

/*----------------------------------------------------------------------------*/

void sensor_init()
{
    mpu9255_set_transfer_frequency(400000);
    if (!is_imu_connected()) {
        process_error();
    }
    
    load_default_configuration();
    new_data_ready = false;
}

bool sensor_is_valid_configuration(struct Sensor_Configuration* config)
{
    if (!config)
        return false;
    if (config->accel_fs_range >= ACCEL_FS_TOP)
        return false;
    if (config->gyro_fs_range >= GYRO_FS_TOP)
        return false;
    if (config->odr >= ODR_TOP)
        return false;
    if (config->adlpf_cfg >= ADLPF_CFG_TOP)
        return false;
    if (config->gdlpf_cfg >= GDLPF_CFG_TOP)
        return false;
    if (config->int_pin_mode >= INT_PIN_MODE_TOP)
        return false;
    if (config->int_mode >= INTERRUPT_MODE_TOP)
        return false;
    if (config->resolution != RESOLUTION)
        return false;
        
    return true;
}

void sensor_get_active_configuration(struct Sensor_Configuration* dest)
{
    if (!dest)
        return;
        
    dest->accel_fs_range = sensor_config.accel_fs_range;
    dest->gyro_fs_range = sensor_config.gyro_fs_range;
    dest->odr = sensor_config.odr;
    dest->adlpf_cfg = sensor_config.adlpf_cfg;
    dest->gdlpf_cfg= sensor_config.gdlpf_cfg;
    dest->int_pin_mode = sensor_config.int_pin_mode;
    dest->int_mode = sensor_config.int_mode;
    dest->resolution = sensor_config.resolution;
}

void sensor_set_default_configuration()
{
    sensor_config.accel_fs_range = SENSOR_DEFAULT_ACCEL_FS_RANGE;
    sensor_config.gyro_fs_range = SENSOR_DEFAULT_GYRO_FS_RANGE;
    sensor_config.odr = SENSOR_DEFAULT_ODR;
    sensor_config.adlpf_cfg = SENSOR_DEFAULT_ADLPF_CFG;
    sensor_config.gdlpf_cfg = SENSOR_DEFAULT_GDLPF_CFG;
    sensor_config.int_pin_mode = INT_PIN_OPEN_DRAIN_FALLING_EDGE;
    sensor_config.int_mode = INTERRUPT_MODE_DATA_RDY;
    sensor_config.resolution = RESOLUTION;
}

void sensor_configure(struct Sensor_Configuration* config)
{
    if (!config)
        return;
        
    configure_accel_fs_range(config->accel_fs_range);
    configure_gyro_fs_range(config->gyro_fs_range);
    configure_odr(config->odr);
    configure_accel_digital_lowpass_filter(config->adlpf_cfg);
    configure_gyro_digital_lowpass_filter(config->gdlpf_cfg);
    configure_int_pin_mode(config->int_pin_mode);
    configure_interrupt_mode(config->int_mode);
}

void sensor_enable_data_ready_interrupt()
{
    imu_int_pin.fall(&imu_interrupt_handler);
}

void sensor_disable_data_ready_interrupt()
{
    imu_int_pin.fall(NULL);
}

bool sensor_is_new_data_ready()
{
    return new_data_ready;
}

void sensor_acquire_sample(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();

    new_data_ready = false;
    
    uint8_t regs_read[14];
    read_imu_data(regs_read);
        
    struct ImuSample new_sample;
    new_sample.ax = ((int16_t)regs_read[0] << 8) + regs_read[1];
    new_sample.ay = ((int16_t)regs_read[2] << 8) + regs_read[3];
    new_sample.az = ((int16_t)regs_read[4] << 8) + regs_read[5];
    new_sample.gx = ((int16_t)regs_read[8] << 8) + regs_read[9];
    new_sample.gy = ((int16_t)regs_read[10] << 8) + regs_read[11];
    new_sample.gz = ((int16_t)regs_read[12] << 8) + regs_read[13];
    buf_replace_next(buf, &new_sample);
}
