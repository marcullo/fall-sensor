#ifndef UI_H_
#define UI_H_

enum UI_Pattern { 
    UI_PATTERN_INIT,
    UI_PATTERN_START_ACQUISITION,
    UI_PATTERN_ACQUISITION_RELOADED,
    UI_PATTERN_STOP_ACQUISITION,
    UI_PATTERN_START_SAVING,
    UI_PATTERN_STOP_SAVING,
    UI_PATTERN_START_DECODING_COMMANDS,
    UI_PATTERN_NONE
};

bool ui_is_main_button_pressed();
bool ui_was_main_button_pressed();
void ui_enable_main_button_interrupt();
void ui_disable_main_button_interrupt();
void ui_clear_main_button_interrupt_status();
void ui_process_pattern(UI_Pattern pattern);

#endif /* UI_H_ */
