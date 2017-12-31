#include "mbed.h" /* Release 150 */
#include "globals.h"
#include "tools/error_handler.h"
#include "sensor/sensor.h"
#include "fall_detector/fall_detector.h"
#include "command_decoder/command_decoder.h"
#include "storage/storage.h"
#include "config_parser/config_parser.h"
#include "transceiver/transceiver.h"
#include "ui/ui.h"

#define IMU_SAMPLES_BEFORE_EVENT_NR     (500)
#define IMU_SAMPLES_AFTER_EVENT_NR      (500)
#define IMU_SAMPLES_NR                  (IMU_SAMPLES_BEFORE_EVENT_NR + IMU_SAMPLES_AFTER_EVENT_NR)
#define HELLO_MESSAGE                   "FSHELLO"
#define OK_MESSAGE                      "FSOK"
#define NOT_OK_MESSAGE                  "FSNOK"
#define NOT_SUPPORTED_COMMAND_MESSAGE   "Command not supported in this mode!"

enum Application_Mode {
    APP_MODE_FALL_DETECTION,
    APP_MODE_DATA_ACQUISITION
} app_mode;

struct ImuSample imu_samples_before_event[IMU_SAMPLES_BEFORE_EVENT_NR];
struct ImuSample imu_samples_after_event[IMU_SAMPLES_AFTER_EVENT_NR];
struct ImuSample imu_samples[IMU_SAMPLES_NR];
char sensor_cfg_buffer[CONFIGURATION_BUF_SIZE];
char message[COMMAND_MAX_LEN];
char command_info[COMMAND_INFO_MAX_LEN];
uint32_t packets_nr;
uint32_t collected_samples_nr;
struct Sensor_Configuration sensor_cfg;
bool panic_enabled;

void acquire_packet(struct ImuBuffer* buf)
{
    if (!buf)
        process_error();    
        
    uint32_t cnt = 0;
    collected_samples_nr = 0;
    
    ui_enable_main_button_interrupt();
    sensor_enable_data_ready_interrupt();
    while (1)
    {
        if (ui_was_main_button_pressed())
            break;
        if(!sensor_is_new_data_ready())
            continue;
        
        sensor_acquire_sample_to_buf(buf);
        
        if (collected_samples_nr < IMU_SAMPLES_NR)
            collected_samples_nr++;
        
        cnt++;
        if (cnt >= IMU_SAMPLES_NR)
        {
            ui_process_pattern(UI_PATTERN_ACQUISITION_RELOADED);
            cnt = 0;
        }    
    }
    ui_disable_main_button_interrupt();
    ui_clear_main_button_interrupt_status();
    sensor_disable_data_ready_interrupt();
}

void flush_packet(struct ImuBuffer* buf)
{
    if (!buf)
        return;
    
    buf_flush(buf);
}

void save_packet(struct ImuBuffer* buf, struct Sensor_Configuration* sensor_cfg)
{
    if (!buf || !sensor_cfg)
        return;
        
    storage_save_packet(buf, packets_nr, collected_samples_nr, sensor_cfg);
    collected_samples_nr = 0;
    packets_nr++;
}

void read_number_of_packets()
{
    packets_nr = storage_get_nr_of_saved_packets();
}

void send_packets_from_storage(struct ImuBuffer* proxy_buf)
{
    if (!proxy_buf)
        return;
    
    struct Sensor_Configuration sensor_cfg;
    uint32_t samples_nr;
    uint32_t packet_nr;
    for (packet_nr = 0; packet_nr < packets_nr; packet_nr++)
    { 
        storage_read_packet(proxy_buf, packet_nr, &sensor_cfg, &samples_nr);
        transceiver_send_packet(proxy_buf, packet_nr, &sensor_cfg, samples_nr);
    }
}

void flush_string(char* str, uint32_t len)
{
    if (!str)
        return;
    
    memset(str, 0, len);
}
void process_pc_commands(struct ImuBuffer* buf)
{
    while(1) 
    {
        flush_string(message, sizeof(message));
        transceiver_receive_message(message);
        enum CommandCode command = decode_message(message);
        switch (command)
        {
        case FS_HELP:
        {
            while (decoder_get_next_command_info(command_info, sizeof(command_info)))
            {
                transceiver_send_message(command_info);
            }
        }
            break;
                    
        case FS_HELLO:
            transceiver_send_message(HELLO_MESSAGE);
            break;
            
        case FS_GOODBYE:
            transceiver_send_message(OK_MESSAGE);
            return;
            
        case FS_RESET:
            transceiver_send_message(OK_MESSAGE);
            wait(0.1);
            NVIC_SystemReset();
            break;
            
        case FS_REMOVE_PACKETS:
            transceiver_send_message(OK_MESSAGE);
            storage_remove_all_packets();
            read_number_of_packets();
            break;
            
        case FS_RESTORE_CONFIG:
            switch (app_mode)
            {
            case APP_MODE_FALL_DETECTION:
                transceiver_send_message(NOT_OK_MESSAGE); 
                transceiver_send_message(NOT_SUPPORTED_COMMAND_MESSAGE);
                break;
            
            case APP_MODE_DATA_ACQUISITION:
                transceiver_send_message(OK_MESSAGE);
                sensor_set_default_configuration();
                sensor_get_active_configuration(&sensor_cfg);
                storage_save_configuration(&sensor_cfg, sensor_cfg_buffer);
                break;
                
            default:
                break;            
            }
            break;
            
        case FS_PACKETS_NR:
            transceiver_send_value(packets_nr);
            break;
        
        case FS_GET_PACKETS:
            send_packets_from_storage(buf);
            storage_remove_all_packets();
            return;
            
        case FS_GET_CONFIG:
            sensor_get_active_configuration(&sensor_cfg);
            if (cfg_parser_print(&sensor_cfg, sensor_cfg_buffer))
            {
                transceiver_send_message(sensor_cfg_buffer);
            }
            break;
            
        case FS_SET_CONFIG:
            switch (app_mode)
            {
            case APP_MODE_FALL_DETECTION:
                transceiver_send_message(NOT_OK_MESSAGE); 
                transceiver_send_message(NOT_SUPPORTED_COMMAND_MESSAGE);
                break;
            
            case APP_MODE_DATA_ACQUISITION:
                transceiver_send_message(OK_MESSAGE);
                transceiver_receive_message(sensor_cfg_buffer);
                
                if (!cfg_parser_scan(sensor_cfg_buffer, &sensor_cfg)) {
                    transceiver_send_message(NOT_OK_MESSAGE);
                    break;
                }
                if (!sensor_is_valid_configuration(&sensor_cfg)) {
                    transceiver_send_message(NOT_OK_MESSAGE);
                    break;
                }
                
                transceiver_send_message(OK_MESSAGE);
                storage_save_configuration(&sensor_cfg, sensor_cfg_buffer);
                sensor_configure(&sensor_cfg);
                break;
                
            default:
                break;            
            }
            break;
            
        default:
            break;            
        }
    }
}

void process_fall_detection(struct ImuBuffer* main_buffer)
{
    if (!main_buffer)
        process_error();
        
    static struct ImuBuffer* imu_buffer_before_event = buf_create(ARRAY_LEN(imu_samples_before_event), imu_samples_before_event);
    if (!imu_buffer_before_event)
        process_error();
    static struct ImuBuffer* imu_buffer_after_event = buf_create(ARRAY_LEN(imu_samples_after_event), imu_samples_after_event);
    if (!imu_buffer_after_event)
        process_error();
    
    fall_detector_init();
    
    sensor_cfg.accel_fs_range =   ACCEL_FS_8G;
    sensor_cfg.gyro_fs_range =    GYRO_FS_1000DPS;
    sensor_cfg.odr =              ODR_100HZ;
    sensor_cfg.adlpf_cfg =        ADLPF_CFG_5HZ;
    sensor_cfg.gdlpf_cfg =        GDLPF_CFG_5HZ;
    sensor_cfg.int_pin_mode =     INT_PIN_OPEN_DRAIN_FALLING_EDGE;
    sensor_cfg.int_mode =         INTERRUPT_MODE_DATA_RDY;
    sensor_cfg.resolution =       SENSOR_RESOLUTION;
    sensor_configure(&sensor_cfg);
    
    fall_detector_configure(sensor_cfg.accel_fs_range, sensor_cfg.gyro_fs_range);

    ImuSample sample;
    while (1)
    {        
        uint32_t samples_after_event_nr = 0;
        collected_samples_nr = 0;
        panic_enabled = false;
        
        read_number_of_packets();
        ui_process_pattern(UI_PATTERN_INIT_MODE1);
        ui_process_pattern(UI_PATTERN_START_ACQUISITION);

        sensor_enable_data_ready_interrupt();
        while (!fall_detector_alarm_occured())
        {
            if(!sensor_is_new_data_ready())
                continue;
            
            sensor_acquire_sample(&sample);
            buf_replace_next(imu_buffer_before_event, &sample);
            fall_detector_process_sample(&sample);
            
            if (collected_samples_nr < IMU_SAMPLES_BEFORE_EVENT_NR)
                collected_samples_nr++;
            if(sensor_is_new_data_ready())
                process_error();
        }
        ui_process_pattern(UI_PATTERN_ALARM_POSSIBLE);
        ui_enable_main_button_interrupt();
        while (samples_after_event_nr < IMU_SAMPLES_AFTER_EVENT_NR)
        {
            if (ui_was_main_button_pressed())
                break;
            if(!sensor_is_new_data_ready())
                continue;
                
            sensor_acquire_sample_to_buf(imu_buffer_after_event);
            collected_samples_nr++;
            samples_after_event_nr++;
            
            if(sensor_is_new_data_ready())
                process_error();
        }
        sensor_disable_data_ready_interrupt();
        ui_disable_main_button_interrupt();
        
        if (!ui_was_main_button_pressed() || !ui_is_main_button_pressed())
        {
            panic_enabled = true;
        }
        ui_clear_main_button_interrupt_status();
   
        while(!buf_is_empty(imu_buffer_before_event))
        {
            buf_read_next(imu_buffer_before_event, &sample);
            buf_replace_next(main_buffer, &sample);
        }
        while(!buf_is_empty(imu_buffer_after_event))
        {
            buf_read_next(imu_buffer_after_event, &sample);
            buf_replace_next(main_buffer, &sample);
        }
        
        sensor_get_active_configuration(&sensor_cfg);
        save_packet(main_buffer, &sensor_cfg);
        buf_flush(main_buffer);
        fall_detector_reset_alarm();
        
        if (panic_enabled)
        {
            ui_process_pattern(UI_PATTERN_ALARM);
            while(1)
                ;
        }
    }
}

void process_data_acquisition(struct ImuBuffer* main_buffer)
{
    if (!main_buffer)
        process_error();
        
    sensor_get_active_configuration(&sensor_cfg);
    if (storage_load_configuration(sensor_cfg_buffer, &sensor_cfg))
    {
        sensor_configure(&sensor_cfg);
    }
    else
    {
        storage_save_configuration(&sensor_cfg, sensor_cfg_buffer);
    }
    
    while (1)
    {
        read_number_of_packets();
        ui_process_pattern(UI_PATTERN_INIT_MODE2);
        
        while(1)
        {
            ui_process_pattern(UI_PATTERN_START_ACQUISITION);
            acquire_packet(main_buffer);
            ui_process_pattern(UI_PATTERN_STOP_ACQUISITION);
    
            if (ui_is_main_button_pressed())
            {
                break;
            }
            else 
            {
                ui_process_pattern(UI_PATTERN_START_SAVING);
                sensor_get_active_configuration(&sensor_cfg);
                save_packet(main_buffer, &sensor_cfg);
                ui_process_pattern(UI_PATTERN_STOP_SAVING);
            }
        }

        ui_process_pattern(UI_PATTERN_START_DECODING_COMMANDS);
        flush_packet(main_buffer);
        process_pc_commands(main_buffer);
    }
}

/*----------------------------------------------------------------------------*/

int main()
{
    static struct ImuBuffer* imu_buffer = buf_create(ARRAY_LEN(imu_samples), imu_samples);
    if (!imu_buffer)
        process_error();
    
    transceiver_init(460800, 8, SerialBase::Even);
    sensor_init();
    
    app_mode = ui_is_main_button_pressed() ? APP_MODE_DATA_ACQUISITION : APP_MODE_FALL_DETECTION;
    while(ui_is_main_button_pressed())
        ;
    
    switch (app_mode)
    {
    case APP_MODE_FALL_DETECTION:
        process_fall_detection(imu_buffer);
        break;
    
    case APP_MODE_DATA_ACQUISITION:
        process_data_acquisition(imu_buffer);
        break;
        
    default:
        process_error();
        break;
    }
    
    while(1)
        ;
}
