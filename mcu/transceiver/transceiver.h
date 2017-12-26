#ifndef TRANSCEIVER_H_
#define TRANSCEIVER_H_

#include "mbed.h"
#include "imu_buffer/imu_buffer.h"
#include "sensor/sensor.h"

void transceiver_init(uint32_t baud_rate, uint32_t data_bits, SerialBase::Parity parity, uint32_t stop_bits = 1);
void transceiver_receive_message(char* buf);
void transceiver_send_message(const char* msg);
void transceiver_send_packet(struct ImuBuffer* buf, uint32_t packet_nr, struct Sensor_Configuration* sensor_cfg, uint32_t samples_nr);
void transceiver_send_value(uint32_t value);

#endif /* TRANSCEIVER_H_ */
