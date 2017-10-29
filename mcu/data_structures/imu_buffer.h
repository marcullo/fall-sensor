/* How to use:
 * 1. Allocate memory (array) for Imu Samples.
 * 2. Allocate memory for buffer using buf_create function.
 * 3. Insert data into buffer circularly (buf_replace_next)
 *    so long as at least to overwrite the oldest values 
 *    (finished full cycle), then buf_is_ready_for_read(..).
 * 4. Stop inserting data into buffer when you are done.
 * 5. Read samples from the oldest to the newest using
 *    buf_read_next function.
 * 6. All data is read when buf_is_all_data_read(..) returns
 *    true.
 *
 */

#ifndef IMU_BUFFER_H
#define IMU_BUFFER_H

#include "imu_data.h"

struct ImuBuffer {
    struct ImuSample* samples;
    uint32_t data_size;
    uint32_t it;
    uint32_t it_read;
    uint32_t size;
    bool overwritten;
    bool reading;
};

struct ImuBuffer* buf_create(uint32_t size, struct ImuSample* samples);
void buf_delete(struct ImuBuffer* buf);

bool buf_is_ready_for_read(struct ImuBuffer* buf);
bool buf_is_all_data_read(struct ImuBuffer* buf);
void buf_replace_next(struct ImuBuffer* buf, struct ImuSample* new_sample);
void buf_read_next(struct ImuBuffer* buf, struct ImuSample* sample);

#endif /* IMU_BUFFER_H */
