#include "ui.h"
#include "pinout.h"
#include "mbed.h"

InterruptIn main_button(UI_MAIN_BUTTON_PIN);
DigitalOut status_led(UI_STATUS_LED_PIN);
PwmOut buzzer(UI_BUZZER_PIN);

static void process_pattern_init();
static void process_pattern_start_acquisition();
static void process_pattern_acquisition_reloaded();
static void process_pattern_stop_acquisition();
static void process_pattern_start_saving();
static void process_pattern_stop_saving();
static void process_pattern_start_decoding_comands();

static void (*operations[])() = {
    &process_pattern_init,
    &process_pattern_start_acquisition,
    *process_pattern_acquisition_reloaded,
    &process_pattern_stop_acquisition,
    &process_pattern_start_saving,
    &process_pattern_stop_saving,
    &process_pattern_start_decoding_comands
};

volatile bool was_main_button_pressed;

static void main_button_handler(void)
{
    was_main_button_pressed = true;
}

static void process_pattern_init()
{
    buzzer.period(1.0f);
    buzzer.write(0.25f);
    wait(1.0);
}

static void process_pattern_start_acquisition()
{
    status_led = !status_led;
    buzzer.write(0.0f);  
}

static void process_pattern_acquisition_reloaded()
{
    status_led = !status_led;
}

static void process_pattern_stop_acquisition()
{
    status_led = !status_led;
    wait(0.5);
}

static void process_pattern_start_saving()
{
    buzzer.write(0.15f);
}

static void process_pattern_stop_saving()
{
    buzzer.write(0.0f);
}

static void process_pattern_start_decoding_comands()
{
    buzzer.write(0.25f);
    wait(1.0);
    buzzer.write(0.0f);
}

/*----------------------------------------------------------------------------*/

bool ui_is_main_button_pressed()
{
    return main_button.read() == 0;
}

bool ui_was_main_button_pressed()
{
    return was_main_button_pressed;
}

void ui_enable_main_button_interrupt()
{
    main_button.fall(&main_button_handler);
}

void ui_disable_main_button_interrupt()
{
    main_button.fall(NULL);
}

void ui_clear_main_button_interrupt_status()
{
    was_main_button_pressed = false;
}

void ui_process_pattern(UI_Pattern pattern)
{    
    if (pattern >= UI_PATTERN_NONE)
        return;
    
    void (*process_operation)();
    process_operation = operations[pattern];
    if (!process_operation)
        return;
    
    process_operation();
}
