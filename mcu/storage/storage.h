#ifndef STORAGE_H_
#define STORAGE_H_

#include "imu_buffer.h"
#include "sensor/sensor.h"

void storage_save_configuration(struct Sensor_Configuration* sensor_cfg, char* cfg_buf);
bool storage_load_configuration(char* cfg_buf, struct Sensor_Configuration* dest_sensor_cfg);
uint32_t storage_get_nr_of_saved_packets();
void storage_save_packet(struct ImuBuffer* buf, uint32_t packet_nr, uint32_t samples_nr, struct Sensor_Configuration* sensor_cfg);
void storage_read_packet(struct ImuBuffer* dest, uint32_t packet_nr, struct Sensor_Configuration* packet_cfg, uint32_t* read_samples_nr);
void storage_remove_all_packets();

#endif /* STORAGE_H_ */
