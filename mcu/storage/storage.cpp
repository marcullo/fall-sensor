#include "storage.h"
#include "pinout.h"
#include "tools/error_handler.h"
#include "globals.h"
#include "SDFileSystem.h" /* 9 Sep 2016 */
#include "config_parser/config_parser.h"

#define DISC_NAME                   "sd"
#define SENSOR_PATH                 "/"DISC_NAME
#define FILE_PATH_LEN               40
#define FILE_EXTENSION              ".DAT"
#define CONFIGURATION_FILE_NAME     "FSCONFIG.INF"
#define CONFIGURATION_FILE_PATH     SENSOR_PATH"/"CONFIGURATION_FILE_NAME
#define IMU_DEGREES_OF_FREEDOM      6

static SDFileSystem sd(
        SD_CARD_MOSI,
        SD_CARD_MISO,
        SD_CARD_SCK,
        SD_CARD_CS,
        DISC_NAME
);
void storage_save_configuration(struct Sensor_Configuration* sensor_cfg, char* cfg_buf)
{
    if (!sensor_cfg || !cfg_buf)
        return;
        
    if (!cfg_parser_print(sensor_cfg, cfg_buf))
        return;
    
    FILE* f = fopen(CONFIGURATION_FILE_PATH, "w");
    if (!f)
        process_error();
        
    fprintf(f,cfg_buf);
    fclose(f);
}

bool storage_load_configuration(char* cfg_buf, struct Sensor_Configuration* dest_sensor_cfg)
{
    if (!dest_sensor_cfg || !cfg_buf)
        return false;

    memset(cfg_buf, 0, sizeof(cfg_buf));
        
    FILE* f = fopen(CONFIGURATION_FILE_PATH, "r");
    if (!f) {
        return false;
    }
    fread(cfg_buf, 1, CONFIGURATION_BUF_SIZE, f);
    fclose(f);

    bool res = cfg_parser_scan(cfg_buf, dest_sensor_cfg);
    return res;
}


uint32_t storage_get_nr_of_saved_packets()
{
    uint32_t packets_nr = 0;
    
    DIR *dp;
    struct dirent *dirp;
    char file_path[FILE_PATH_LEN];

    dp = opendir(SENSOR_PATH);
    while((dirp = readdir(dp)) != NULL) 
    {
        const char* file_name = dirp->d_name;
        if (!strstr(file_name, FILE_EXTENSION))
            continue;
        
        sprintf(file_path, "%s/%s", SENSOR_PATH, dirp->d_name);
        FILE* f = fopen(file_path, "r");
        if (f) 
        {
            packets_nr++;
        }
        fclose(f);
    }
    closedir(dp);
    
    return packets_nr;
}

void storage_save_packet(struct ImuBuffer* buf, uint32_t packet_nr, uint32_t samples_nr, struct Sensor_Configuration* sensor_cfg)
{
    if (!buf || !sensor_cfg)
        return;
    
    char file_path[FILE_PATH_LEN];
    sprintf(file_path, "/%s/%04x"FILE_EXTENSION, DISC_NAME, packet_nr);
    FILE* f = fopen(file_path, "w");
    if (!f)
        process_error();
    
    fprintf(f, "FS");
    
    fprintf(f, "%04x%04x%04x%04x", 
            (uint16_t)sensor_cfg->accel_fs_range, 
            (uint16_t)sensor_cfg->gyro_fs_range,
            (uint16_t)sensor_cfg->odr,
            (uint16_t)sensor_cfg->resolution);
            
    fprintf(f, "%04x%04x%04x%04x", 
            (uint16_t)sensor_cfg->adlpf_cfg, 
            (uint16_t)sensor_cfg->gdlpf_cfg,
            (uint16_t)sensor_cfg->int_pin_mode,
            (uint16_t)sensor_cfg->int_mode);  
              
    fprintf(f, "%04x", samples_nr);
    
    struct ImuSample new_sample;
    while(!buf_is_empty(buf))
    {
        buf_read_next(buf, &new_sample);
        
        fprintf(f, "%04x%04x%04x",
            (uint16_t)new_sample.ax,
            (uint16_t)new_sample.ay,
            (uint16_t)new_sample.az);
            
        fprintf(f, "%04x%04x%04x",
            (uint16_t)new_sample.gx,
            (uint16_t)new_sample.gy,
            (uint16_t)new_sample.gz);
    }
    
    fprintf(f, "\r\n");
    fclose(f);
}

void storage_read_packet(struct ImuBuffer* dest, uint32_t packet_nr, struct Sensor_Configuration* packet_cfg, uint32_t* read_samples_nr)
{
    if (!dest || !read_samples_nr)
        return;    
    
    struct ImuSample new_sample;
    int16_t* sample_elem = &(new_sample.ax);
        
    char fbuf[5];
    fbuf[4] = '\0';
    int read_cnt = 0;
    char file_path[FILE_PATH_LEN];
    
    sprintf(file_path, "/%s/%04x"FILE_EXTENSION, DISC_NAME, packet_nr);
    
    FILE* f = fopen(file_path, "r");
    if (!f)
        process_error();

    read_cnt = fread(fbuf, 1, 2, f);
    fbuf[read_cnt] = '\0';
    if (strcmp(fbuf, "FS") != 0)
        process_error();
      
    uint32_t read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= ACCEL_FS_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->accel_fs_range = (enum Sensor_Accel_Full_Scale_Range) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= GYRO_FS_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->gyro_fs_range = (enum Sensor_Gyro_Full_Scale_Range) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= ODR_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->odr = (enum Sensor_Output_Data_Rate) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val > 16 || read_val == 0)
    {
        fclose(f);
        return;
    }
    packet_cfg->resolution = (uint32_t) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= ADLPF_CFG_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->adlpf_cfg = (enum Sensor_Accel_Digital_Lowpass_Config) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= GDLPF_CFG_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->gdlpf_cfg = (enum Sensor_Gyro_Digital_Lowpass_Config) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= INT_PIN_MODE_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->int_pin_mode = (enum Sensor_Interrupt_Pin_Mode) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    if (read_val >= INTERRUPT_MODE_TOP)
    {
        fclose(f);
        return;
    }
    packet_cfg->int_mode = (enum Sensor_Interrupt_Mode) read_val;
    
    /**/
    read_cnt = fread(fbuf, 1, 4, f);
    fbuf[read_cnt] = '\0';
    read_val = strtoul(fbuf, NULL, 16);
    uint32_t samples_nr = read_val;
    *read_samples_nr = samples_nr;
    if (read_val == 0)
    {
        fclose(f);
        return;
    }
     
    uint32_t i;
    for (i = 0; i < samples_nr * IMU_DEGREES_OF_FREEDOM; i++)
    {
        read_cnt = fread(fbuf, 1, 4, f);
        if (read_cnt < 4)
            break;
            
        *sample_elem = (int16_t)strtoul(fbuf, NULL, 16);
        sample_elem++;
        
        if (i % IMU_DEGREES_OF_FREEDOM == (IMU_DEGREES_OF_FREEDOM - 1))
        {
            sample_elem = &(new_sample.ax);
            buf_replace_next(dest, &new_sample);
        }
    }
    if (read_cnt < 4)
        process_error();
        
    fclose(f);
}

void storage_remove_all_packets()
{
    char file_path[FILE_PATH_LEN];
    DIR *dp;
    struct dirent *dirp;
    dp = opendir(SENSOR_PATH);
    
    while((dirp = readdir(dp)) != NULL) {
        sprintf(file_path, "%s/%s", SENSOR_PATH, dirp->d_name);
        
        FILE* f = fopen(file_path, "r");
        if (!f)
            continue;
        fclose(f);
        
        int res = remove(file_path);
        if (res != 0)
            process_error();
    }
    closedir(dp);
}
