#ifndef MPU9255_H_
#define MPU9255_H_

#include <stdint.h>

bool mpu9255_is_connected();
void mpu9255_init();
void mpu9255_read_data(uint8_t* data);

#endif /* MPU9255_H_ */
