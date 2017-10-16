#ifndef MPU9255_H_
#define MPU9255_H_

#include <stdint.h>

bool mpu9255_is_connected();
void mpu9255_init();
void mpu9255_accel_read_data_regs(uint8_t* data);
void mpu9255_gyro_read_data_regs(uint8_t* data);

#endif /* MPU9255_H_ */
