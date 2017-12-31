#ifndef FALL_DETECTOR_H_
#define FALL_DETECTOR_H_

#include "sensor/sensor.h"

void fall_detector_init();
void fall_detector_configure(enum Sensor_Accel_Full_Scale_Range accel_fs_range, enum Sensor_Gyro_Full_Scale_Range gyro_fs_range);
void fall_detector_process_sample(struct ImuSample* sample);
bool fall_detector_alarm_occured();
void fall_detector_reset_alarm();

#endif /* FALL_DETECTOR_H_ */
