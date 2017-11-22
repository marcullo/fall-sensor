#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#include "mbed.h"

inline void process_error()
{
    static int led_state = 0;
    DigitalOut errorLed(LED1);
    PwmOut buzzer(PA_8);
    
    buzzer.period(0.3);
    buzzer.write(0.15f);
    
    wait(1.2);
    
    buzzer.write(0.0f);
    
    while (1) 
    {
        led_state = !led_state;
        errorLed.write(led_state);
        wait(0.2);
    }
}

#endif /* ERROR_HANDLER_H_ */