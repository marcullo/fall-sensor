#include "fall_detector.h"
#include "globals.h"

#define MEASUREMENT_MAX_VAL                 (32767)
#define MEASUREMENT_MIN_VAL                 (-32767-1)

#define CRASH_BUF_SIZE                      5
#define CRASH_THR_ACCL_SWELL_BIG_G          8.0
#define CRASH_THR_ACCL_SWELL_G              4.5
#define CRASH_THR_GYRO_SWELL_DPS            400.0

enum Detector_State {
    STATE_IDLE,
    STATE_DETECT_CRASH,
    STATE_FALL_DETECTED,   
    STATE_TOP
};

static struct fall_detector_context {
    struct ImuSample crash_samples[CRASH_BUF_SIZE];
    struct ImuSample samples_tmp[CRASH_BUF_SIZE];
    struct ImuBuffer* crash_buffer;
    /* CRASH */
    uint32_t crash_accl_swell_raw[3];
    uint32_t crash_gyro_swell_raw[3];
    uint32_t crash_thr_accl_swell_big_raw;
    uint32_t crash_thr_accl_swell_raw;
    uint32_t crash_thr_gyro_swell_raw;
    /* STATE */
    enum Detector_State state;
} ctx;

bool configure_accl_fs_range_div(enum Sensor_Accel_Full_Scale_Range fs_range, uint32_t* div)
{
    if (!div)
        return false;
    
    switch (fs_range)
    {
    case ACCEL_FS_2G:
        *div = 2;
        break;
        
    case ACCEL_FS_4G:
        *div = 4;
        break;
        
    case ACCEL_FS_8G:
        *div = 8;
        break;
        
    case ACCEL_FS_16G:
        *div = 16;
        break;
        
    default:
        return false;
    }
    
    return true;
}

bool configure_gyro_fs_range_div(enum Sensor_Gyro_Full_Scale_Range fs_range, uint32_t* div)
{
    if (!div)
        return false;
    
    switch (fs_range)
    {
    case GYRO_FS_250DPS:
        *div = 250;
        break;
        
    case GYRO_FS_500DPS:
        *div = 500;
        break;
        
    case GYRO_FS_1000DPS:
        *div = 1000;
        break;
        
    case GYRO_FS_2000DPS:
        *div = 2000;
        break;
        
    default:
        return false;
    }
    
    return true;
}

bool detect_crash(struct ImuSample* sample)
{
    if (!sample)
        return false;
    
    buf_replace_next(ctx.crash_buffer, sample);
    if (!buf_is_full(ctx.crash_buffer))
        return false;
    
    int32_t max_val[6];
    int32_t min_val[6];
    uint32_t i;
    
    for (i = 0; i < 6; i++)
    {
        max_val[i] = MEASUREMENT_MIN_VAL;
        min_val[i] = MEASUREMENT_MAX_VAL;
    }
    
    for (i = 0; i < CRASH_BUF_SIZE; i++)
    {
        buf_read_next(ctx.crash_buffer, &ctx.samples_tmp[i]);
    }
    
    for (i = 0; i < CRASH_BUF_SIZE; i++)
    {
        max_val[0] = MAX(ctx.samples_tmp[i].ax, max_val[0]);
        min_val[0] = MIN(ctx.samples_tmp[i].ax, min_val[0]);
        max_val[1] = MAX(ctx.samples_tmp[i].ay, max_val[1]);
        min_val[1] = MIN(ctx.samples_tmp[i].ay, min_val[1]);
        max_val[2] = MAX(ctx.samples_tmp[i].az, max_val[2]);
        min_val[2] = MIN(ctx.samples_tmp[i].az, min_val[2]);
        
        max_val[3] = MAX(ctx.samples_tmp[i].gx, max_val[3]);
        min_val[3] = MIN(ctx.samples_tmp[i].gx, min_val[3]);
        max_val[4] = MAX(ctx.samples_tmp[i].gy, max_val[4]);
        min_val[4] = MIN(ctx.samples_tmp[i].gy, min_val[4]);
        max_val[5] = MAX(ctx.samples_tmp[i].gz, max_val[5]);
        min_val[5] = MIN(ctx.samples_tmp[i].gz, min_val[5]);
    }
    ctx.crash_accl_swell_raw[0] = max_val[0] - min_val[0];
    ctx.crash_accl_swell_raw[1] = max_val[1] - min_val[1];
    ctx.crash_accl_swell_raw[2] = max_val[2] - min_val[2];
    ctx.crash_gyro_swell_raw[0] = max_val[3] - min_val[3];
    ctx.crash_gyro_swell_raw[1] = max_val[4] - min_val[4];
    ctx.crash_gyro_swell_raw[2] = max_val[5] - min_val[5];
    
    for (i = 0; i < CRASH_BUF_SIZE; i++)
    {
        buf_replace_next(ctx.crash_buffer, &ctx.samples_tmp[i]);
    }
    
    if (ctx.crash_accl_swell_raw[0] > ctx.crash_thr_accl_swell_big_raw)
    {
        return true;
    }
    else if (ctx.crash_accl_swell_raw[1] > ctx.crash_thr_accl_swell_big_raw)
    {
        return true;
    }
    else if (ctx.crash_accl_swell_raw[2] > ctx.crash_thr_accl_swell_big_raw)
    {
        return true;
    }
    else if (ctx.crash_accl_swell_raw[0] > ctx.crash_thr_accl_swell_raw
        && ctx.crash_gyro_swell_raw[0] > ctx.crash_thr_gyro_swell_raw)  
    {
        return true;
    }
    else if (ctx.crash_accl_swell_raw[1] > ctx.crash_thr_accl_swell_raw
        && ctx.crash_gyro_swell_raw[1] > ctx.crash_thr_gyro_swell_raw)  
    {
        return true;
    }
    else if (ctx.crash_accl_swell_raw[2] > ctx.crash_thr_accl_swell_raw
        && ctx.crash_gyro_swell_raw[2] > ctx.crash_thr_gyro_swell_raw)  
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*----------------------------------------------------------------------------*/

void fall_detector_init()
{    
    ctx.crash_buffer = buf_create(ARRAY_LEN(ctx.crash_samples), ctx.crash_samples);
    if (!ctx.crash_buffer)
        return;
}

void fall_detector_configure(enum Sensor_Accel_Full_Scale_Range accel_fs_range, enum Sensor_Gyro_Full_Scale_Range gyro_fs_range)
{
    if (!ctx.crash_buffer)
        return;

    ctx.state =  STATE_IDLE;
    
    uint32_t accl_fs_range_div;
    uint32_t gyro_fs_range_div;
    
    if (!configure_accl_fs_range_div(accel_fs_range, &accl_fs_range_div))
        return;
    if (!configure_gyro_fs_range_div(gyro_fs_range, &gyro_fs_range_div))
        return;
    
    ctx.crash_thr_accl_swell_big_raw = (int32_t)(CRASH_THR_ACCL_SWELL_BIG_G * MEASUREMENT_MAX_VAL / (float)accl_fs_range_div);
    ctx.crash_thr_accl_swell_raw = (int32_t)(CRASH_THR_ACCL_SWELL_G * MEASUREMENT_MAX_VAL / (float)accl_fs_range_div);
    ctx.crash_thr_gyro_swell_raw = (int32_t)(CRASH_THR_GYRO_SWELL_DPS * MEASUREMENT_MAX_VAL / (float)gyro_fs_range_div);

    ctx.state =  STATE_DETECT_CRASH;
}

void fall_detector_process_sample(struct ImuSample* sample)
{
    if (!sample)
        return;
    
    bool res;
    
    switch (ctx.state)
    {
    case STATE_DETECT_CRASH:
        res = detect_crash(sample);
        if (res) 
        {
            ctx.state = STATE_FALL_DETECTED;
        }
        break;

    default:
        break;
    }
}

bool fall_detector_alarm_occured()
{
    return ctx.state == STATE_FALL_DETECTED;
}

void fall_detector_reset_alarm()
{
    buf_flush(ctx.crash_buffer);
    ctx.state = STATE_DETECT_CRASH;
}
