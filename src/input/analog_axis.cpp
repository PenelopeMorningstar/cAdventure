#include "input/analog_axis.hpp"


AnalogAxis::AnalogAxis(int key_code): key_code_(key_code) {
    key_code_ = key_code;
}


void AnalogAxis::Update(){
    int new_value = 0;

    if (key_code_ == CURSOR_X_KEY_CODE_) {
        new_value = g_cursor_manager->GetXPos();
    }
    if (key_code_ == CURSOR_Y_KEY_CODE_) {
        new_value = g_cursor_manager->GetYPos();
    }

    int last_value_ = value_;
    int value_ = new_value;
    int delta_ = value_ - last_value_;
}
