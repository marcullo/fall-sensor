/* How to use:
 *
 * 1. Allocate array for samples
 *        struct ImuSamples samples[SAMPLES_NR];
 * 2. Allocate memory for buffer
 *        struct ImuBuffer* buf = buf_create(SAMPLES_NR, samples);
 * 3. To insert sample into buffer
 *        buf_replace_next(buf, new_sample);
 * 4. To read the oldest sample
 *        if (!buf_is_empty(buf))
 *            buf_read_next(buf, oldest_sample);
 * 
 * Note:
 *     This is a FIFO circular buffer (oldest sample is overwritten when you add
 *     a new one when the buffer is full).
 */
#ifndef IMU_BUFFER_H
#define IMU_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

struct ImuSample {
    uint16_t accel_x;
    uint16_t accel_y;
    uint16_t accel_z;
    uint16_t gyro_x;
    uint16_t gyro_y;
    uint16_t gyro_z;
};

struct ImuBuffer {
    struct ImuSample* _samples;
    uint32_t _sample_size;
    uint32_t _size;
    uint32_t _wr;
    uint32_t _re;
    bool _full;
    bool _empty;
};

struct ImuBuffer* buf_create(uint32_t size, struct ImuSample* samples);
void buf_delete(struct ImuBuffer* buf);

bool buf_is_full(struct ImuBuffer* buf);
bool buf_is_empty(struct ImuBuffer* buf);
void buf_replace_next(struct ImuBuffer* buf, struct ImuSample* new_sample);
void buf_read_next(struct ImuBuffer* buf, struct ImuSample* sample);

#endif /* IMU_BUFFER_H */
