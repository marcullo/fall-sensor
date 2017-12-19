#include "mbed.h" /* Release 150 */
#include "sensor/sensor.h"
#include "imu_buffer/imu_buffer.h"
#include "tools/error_handler.h"
#include "tools/global_def.h"
#include "command_decoder/command_decoder.h"
#include "storage/storage.h"
#include "transceiver/transceiver.h"
#include "ui/ui.h"
#include "config_parser/config_parser.h"
#include <stdlib.h>

#define IMU_SAMPLES_NR          1000
#define COLLECTING_FREQUENCY    100
#define HELLO_MESSAGE           "FSHELLO\r"
#define OK_MESSAGE              "OK\r"

struct ImuSample imu_samples[IMU_SAMPLES_NR];
char sensor_cfg_buffer[CONFIGURATION_BUF_SIZE];
char message[COMMAND_MAX_LEN];
uint32_t packets_nr;
uint32_t collected_samples_nr;
struct Sensor_Configuration sensor_cfg;

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
        
        sensor_acquire_sample(buf);
        
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
        flush_string(message, COMMAND_MAX_LEN);
        transceiver_receive_message(message);
        enum CommandCode command = decode_message(message);
        switch (command)
        {
        case FS_HELLO:
            transceiver_send_text(HELLO_MESSAGE);
            break;
            
        case FS_GOODBYE:
            transceiver_send_text(OK_MESSAGE);
            return;
            
        case FS_RESET:
            transceiver_send_text(OK_MESSAGE);
            wait(0.1);
            NVIC_SystemReset();
            break;
            
        case FS_REMOVE_PACKETS:
            transceiver_send_text(OK_MESSAGE);
            storage_remove_all_packets();
            read_number_of_packets();
            break;
            
        case FS_PACKETS_NR:
            transceiver_send_value(packets_nr);
            break;
            
        case FS_FREQUENCY:
            transceiver_send_value(COLLECTING_FREQUENCY);
            break;
        
        case FS_GET_PACKETS:
            send_packets_from_storage(buf);
            storage_remove_all_packets();
            return;
            
        default:
            break;            
        }
    }
}

/*----------------------------------------------------------------------------*/

int main()
{
    static struct ImuBuffer* imu_buffer = buf_create(ARRAY_LEN(imu_samples), imu_samples);
    if (!imu_buffer)
        process_error();

    transceiver_init(921600, 8, SerialBase::Even);
    sensor_init();
    
    sensor_get_active_configuration(&sensor_cfg);
    if (storage_load_configuration(sensor_cfg_buffer, &sensor_cfg))
    {
        sensor_configure(&sensor_cfg);
    }
    
    while (1)
    {
        read_number_of_packets();
        ui_process_pattern(UI_PATTERN_INIT);
        
        while(1)
        {
            ui_process_pattern(UI_PATTERN_START_ACQUISITION);
            acquire_packet(imu_buffer);
            ui_process_pattern(UI_PATTERN_STOP_ACQUISITION);
    
            if (ui_is_main_button_pressed())
            {
                break;
            }
            else 
            {
                ui_process_pattern(UI_PATTERN_START_SAVING);
                sensor_get_active_configuration(&sensor_cfg);
                save_packet(imu_buffer, &sensor_cfg);
                ui_process_pattern(UI_PATTERN_STOP_SAVING);
            }
        }

        ui_process_pattern(UI_PATTERN_START_DECODING_COMMANDS);
        flush_packet(imu_buffer);
        process_pc_commands(imu_buffer);
    }
}

