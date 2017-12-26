#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#include "mbed.h"
#include "pinout.h"

inline void process_error()
{
    static int led_state = 0;
    DigitalOut errorLed(UI_STATUS_LED_PIN);
    PwmOut buzzer(UI_BUZZER_PIN);
    
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