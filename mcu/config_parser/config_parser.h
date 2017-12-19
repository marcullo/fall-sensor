#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include "sensor/sensor.h"

#define CONFIGURATION_BUF_SIZE 2048

bool cfg_parser_print(struct Sensor_Configuration* sensor_cfg, char* dest);
bool cfg_parser_scan(const char* src, struct Sensor_Configuration* sensor_cfg_dest);

#endif /* CONFIG_PARSER_H_ */
