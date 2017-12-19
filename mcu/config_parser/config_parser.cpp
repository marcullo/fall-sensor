#include "config_parser.h"
#include <stddef.h>
#include "json/cJSON.h"
#include "command_decoder/string_data.h"

#define SENSOR_CONFIGURATION_NAME   "SensorConfiguration"

enum Configuration_Register {
    ACCEL_FS_RANGE,
    GYRO_FS_RANGE,
    OUTPUT_DATA_RATE,
    ACCEL_DLPF_CFG,
    GYRO_DLPF_CFG,
    INTERRUPT_PIN_MODE,
    INTERRUPT_MODE,
    RESOLUTION,
    CONFIG_MEMBER_TOP
};

static const char* configuration_members_names[] = {
    "AccelFSRange",
    "GyroFSRange",
    "Frequency",
    "AccelDLPFFrequency",
    "GyroDLPFFrequency",
    "InterruptPinMode",
    "InterruptMode",
    "Resolution",
};

static const char* sensor_accel_fs_range_names[] = {
    "2G",
    "4G",
    "8G",
    "16G",
    NULL
};

static const char* sensor_gyro_fs_range_names[] = {
    "250DPS",
    "500DPS",
    "1000DPS",
    "2000DPS",
    NULL
};

static const char* sensor_odr_names[] = {
    "10HZ",
    "20HZ",
    "40HZ",
    "50HZ",
    "100HZ",
    "200HZ",
    "500HZ",
    "1000HZ",
    NULL
};

static const char* sensor_adlpf_cfg_names[] = {
    "5HZ",
    "10HZ",
    "20HZ",
    "41HZ",
    "92HZ",
    "184HZ",
    "460HZ",
    NULL
};

static const char* sensor_gdlpf_cfg_names[] = {
    "5HZ",
    "10HZ",
    "20HZ",
    "41HZ",
    "92HZ",
    "184HZ",
    NULL
};

static const char* sensor_int_pin_mode_names[] = {
    "OPEN_DRAIN_FALLING_EDGE",
    NULL
};

static const char* sensor_int_mode_names[] = {
    "DATA_RDY",
    NULL
};

static bool get_value_from_json(cJSON *sensor_cfg_json, int cfg_member, const char** cfg_member_values, int* new_value)
{
    if (!sensor_cfg_json || !cfg_member_values || !new_value || cfg_member >= CONFIG_MEMBER_TOP)
        return false;

    const char* name = configuration_members_names[cfg_member];
    cJSON* scfg_item = cJSON_GetObjectItem(sensor_cfg_json, name);
    if (cJSON_IsString(scfg_item))
    {        
        const char* value = scfg_item->valuestring;
        int member_value_id = strinarrayid(value, cfg_member_values);
        if (member_value_id >= 0)
        {
            *new_value = member_value_id;
            return true;
        }
    } 
    return false;
}

/*----------------------------------------------------------------------------*/

bool cfg_parser_print(struct Sensor_Configuration* sensor_cfg, char* dest)
{
    if (!sensor_cfg || !dest || !sensor_is_valid_configuration(sensor_cfg))
        return false;
       
    cJSON *root;
    cJSON *scfg;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, SENSOR_CONFIGURATION_NAME, scfg = cJSON_CreateObject());

    const char* name;
    const char* value;
    
    name = configuration_members_names[ACCEL_FS_RANGE];
    value = sensor_accel_fs_range_names[sensor_cfg->accel_fs_range];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[GYRO_FS_RANGE];
    value = sensor_gyro_fs_range_names[sensor_cfg->gyro_fs_range];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[OUTPUT_DATA_RATE];
    value = sensor_odr_names[sensor_cfg->odr];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[ACCEL_DLPF_CFG];
    value = sensor_adlpf_cfg_names[sensor_cfg->adlpf_cfg];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[GYRO_DLPF_CFG];
    value = sensor_gdlpf_cfg_names[sensor_cfg->gdlpf_cfg];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[INTERRUPT_PIN_MODE];
    value = sensor_int_pin_mode_names[sensor_cfg->int_pin_mode];
    cJSON_AddStringToObject(scfg, name, value);

    name = configuration_members_names[INTERRUPT_MODE];
    value = sensor_int_mode_names[sensor_cfg->int_mode];
    cJSON_AddStringToObject(scfg, name, value);
    
    name = configuration_members_names[RESOLUTION];
    cJSON_AddNumberToObject(scfg, name, sensor_cfg->resolution);
    
    bool res = cJSON_PrintPreallocated(root, dest, CONFIGURATION_BUF_SIZE, false);
    cJSON_Delete(root);
    
    return res;
}

bool cfg_parser_scan(const char* src, struct Sensor_Configuration* sensor_cfg_dest)
{
    if (!src || !sensor_cfg_dest)
        return false;
        
    int new_value;
    cJSON * root = cJSON_Parse(src);    
    cJSON *scfg = cJSON_GetObjectItem(root, SENSOR_CONFIGURATION_NAME);
    
    if (!get_value_from_json(scfg, ACCEL_FS_RANGE, sensor_accel_fs_range_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->accel_fs_range = (enum Sensor_Accel_Full_Scale_Range) new_value;

    if (!get_value_from_json(scfg, GYRO_FS_RANGE, sensor_gyro_fs_range_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->gyro_fs_range = (enum Sensor_Gyro_Full_Scale_Range) new_value;
    
    if (!get_value_from_json(scfg, OUTPUT_DATA_RATE, sensor_odr_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->odr = (enum Sensor_Output_Data_Rate) new_value;
    
    if (!get_value_from_json(scfg, ACCEL_DLPF_CFG, sensor_adlpf_cfg_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->adlpf_cfg = (enum Sensor_Accel_Digital_Lowpass_Config) new_value;
    
    if (!get_value_from_json(scfg, GYRO_DLPF_CFG, sensor_gdlpf_cfg_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->gdlpf_cfg = (enum Sensor_Gyro_Digital_Lowpass_Config) new_value;
        
    if (!get_value_from_json(scfg, INTERRUPT_PIN_MODE, sensor_int_pin_mode_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->int_pin_mode = (enum Sensor_Interrupt_Pin_Mode) new_value;
    
    if (!get_value_from_json(scfg, INTERRUPT_MODE, sensor_int_mode_names, &new_value)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->int_mode = (enum Sensor_Interrupt_Mode) new_value;
    
    const char* name = configuration_members_names[RESOLUTION];
    cJSON* scfg_item = cJSON_GetObjectItem(scfg, name);
    if (!cJSON_IsNumber(scfg_item)) {
        cJSON_Delete(root);
        return false;
    }
    sensor_cfg_dest->resolution = (uint32_t) scfg_item->valuedouble;
    
    cJSON_Delete(root);
    return true;
}


