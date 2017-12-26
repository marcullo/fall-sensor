#include "transceiver.h"
#include "pinout.h"

Serial pc(SERIAL_TX_PIN, SERIAL_RX_PIN);

void transceiver_init(uint32_t baud_rate, uint32_t data_bits, SerialBase::Parity parity, uint32_t stop_bits)
{
    pc.baud(baud_rate);
    pc.format(data_bits, SerialBase::Even, stop_bits);
}

void transceiver_receive_message(char* buf)
{
    if (!buf)
        return;
        
    pc.scanf("%s", buf);
}

void transceiver_send_message(const char* msg)
{
    if (!msg)
        return;

    pc.printf("%s\r", msg);
}

void transceiver_send_packet(struct ImuBuffer* buf, uint32_t packet_nr, struct Sensor_Configuration* sensor_cfg, uint32_t samples_nr)
{    
    if (!buf || !sensor_cfg)
        return;

    pc.printf("FS");
    
    pc.printf("%04x", packet_nr);
    
    pc.printf("%04x%04x%04x%04x",
            (uint16_t)sensor_cfg->accel_fs_range, 
            (uint16_t)sensor_cfg->gyro_fs_range,
            (uint16_t)sensor_cfg->odr,
            (uint16_t)sensor_cfg->resolution);

    pc.printf("%04x", samples_nr);
    
    struct ImuSample new_sample;
    while(!buf_is_empty(buf))
    {
        buf_read_next(buf, &new_sample);
        
        pc.printf("%04x%04x%04x",
            (uint16_t)new_sample.ax,
            (uint16_t)new_sample.ay,
            (uint16_t)new_sample.az);
            
        pc.printf("%04x%04x%04x",
            (uint16_t)new_sample.gx,
            (uint16_t)new_sample.gy,
            (uint16_t)new_sample.gz);
    }
    
    pc.printf("\r");
}

void transceiver_send_value(uint32_t value)
{
    pc.printf("FS%04x\r", value);
}
