#ifndef IMU_DATA_H
#define IMU_DATA_H

#include <stdint.h>

struct ImuSample {
    uint16_t accel_x;
    uint16_t accel_y;
    uint16_t accel_z;
    uint16_t gyro_x;
    uint16_t gyro_y;
    uint16_t gyro_z;
};

#endif /* IMU_DATA_H */