#include "imu_buffer.h"
#include <stdlib.h>
#include <string.h>

static void increment_write_id(struct ImuBuffer* buf)
{
    if (!buf || buf->_size == 0)
        return;
    
    buf->_wr++;
    if (buf->_wr == buf->_size)
        buf->_wr = 0;
}

static void increment_read_id(struct ImuBuffer* buf)
{
    if (!buf || buf->_size == 0)
        return;
    
    buf->_re++;
    if (buf->_re == buf->_size)
        buf->_re = 0;
}

//-----------------------------------------------------------------------------

struct ImuBuffer* buf_create(uint32_t size, struct ImuSample* samples)
{
    if (size == 0 || !samples)
        return NULL;
        
    struct ImuBuffer* new_buffer = (struct ImuBuffer*)malloc(sizeof(struct ImuBuffer));
    if (!new_buffer)
        return NULL;

    new_buffer->_samples = samples;
    new_buffer->_sample_size = sizeof(struct ImuSample);
    new_buffer->_size = size;
    memset(new_buffer->_samples, 0, new_buffer->_size * new_buffer->_sample_size);
    
    new_buffer->_wr = 0;
    new_buffer->_re = 0;
    new_buffer->_full = false;
    new_buffer->_empty = true;
    
    return new_buffer;
}

void buf_delete(struct ImuBuffer* buf)
{
    if (!buf)
        return;
    
   free(buf);
   buf = NULL;
}

bool buf_is_full(struct ImuBuffer* buf)
{
    return (buf && buf->_full);
}

bool buf_is_empty(struct ImuBuffer* buf)
{
    return (buf && buf->_empty);
}

void buf_flush(struct ImuBuffer* buf)
{
    if (!buf)
        return;
        
    struct ImuSample dummy;
    while (!buf_is_empty(buf))
    {
        buf_read_next(buf, &dummy);
    }
}

void buf_replace_next(struct ImuBuffer* buf, struct ImuSample* new_sample)
{
    if (!buf || !new_sample)
        return;
    
    struct ImuSample* sample_it = buf->_samples + buf->_wr;
    memcpy(sample_it, new_sample, buf->_sample_size);
    
    buf->_empty = false;
    
    if (buf->_full)
    {
        increment_read_id(buf);
    }
    increment_write_id(buf);
    if (buf->_wr == buf->_re)
    {
        buf->_full = true;
    }
}

void buf_read_next(struct ImuBuffer* buf, struct ImuSample* sample)
{
    if (!buf || !sample || buf->_empty)
        return;
       
    struct ImuSample* sample_it = buf->_samples + buf->_re;
    memcpy(sample, sample_it, buf->_sample_size);
    
    buf->_full = false;
    
    increment_read_id(buf);
    if (buf->_re == buf->_wr)
    {
        buf->_empty = true;
    }
}
