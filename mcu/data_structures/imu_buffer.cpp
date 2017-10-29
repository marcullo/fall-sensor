#include "imu_buffer.h"

#include <stdlib.h>
#include <string.h>

struct ImuBuffer* buf_create(uint32_t size, struct ImuSample* samples)
{
    if (!size || !samples)
        return NULL;
        
    struct ImuBuffer* new_buffer = (struct ImuBuffer*)malloc(sizeof(struct ImuBuffer));
    if (!new_buffer)
        return NULL;

    new_buffer->reading = false;
    new_buffer->overwritten = false;
    new_buffer->it = 0;
    new_buffer->samples = samples;
    new_buffer->size = size;
    new_buffer->data_size = sizeof(struct ImuSample);
    memset(new_buffer->samples, 0, new_buffer->size * new_buffer->data_size);
    
    return new_buffer;
}

void buf_delete(struct ImuBuffer* buf)
{
    if (!buf)
        return;
   
   free(buf);
}


bool buf_is_ready_for_read(struct ImuBuffer* buf)
{
    if (!buf || !buf->overwritten)
        return false;
    
    return true;
}

bool buf_is_all_data_read(struct ImuBuffer* buf)
{
    if (!buf)
        return false;
    if (buf->it_read == buf->it + 1)
    {
        buf->reading = false;
        return true;
    }
    return false;        
}

void buf_replace_next(struct ImuBuffer* buf, struct ImuSample* new_sample)
{
    if (!buf || !new_sample || buf->reading)
        return;
    
    memcpy(buf->samples + buf->it, new_sample, buf->data_size);
       
    buf->it++;
    buf->it_read++;
    if (buf->it == buf->size)
    {
        buf->it = 0;
        buf->it_read = buf->it + 1;
        buf->overwritten = true;
    }
    else if (buf->it_read == buf->size)
    {
        buf->it_read = 0;
    }    
}

void buf_read_next(struct ImuBuffer* buf, struct ImuSample* sample)
{
    if (!buf || !sample || !buf->overwritten)
        return;
    
    buf->reading = true;
       
    memcpy(sample, buf->samples + buf->it_read, buf->data_size);
    buf->it_read++;
    if (!buf_is_all_data_read(buf))
        buf->it_read %= buf->size;
}
