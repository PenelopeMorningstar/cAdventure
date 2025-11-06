#include "input/input.hpp"
#include "input/io_key.hpp"
#include "input/analog_axis.hpp"


InputManager::InputManager() {
    // create digital keys
    digital_keys_ = {
        {"left", new IOKey(0x41)},
        {"right", new IOKey(0x44)},
        {"up", new IOKey(0x57)},
        {"down", new IOKey(0x53)}
    };

    // create analog axis
    analog_axis_ = {
        {"cursor_x", new AnalogAxis(1)},  // 1 is left click
        {"cursor_y", new AnalogAxis(2)}  // 2 is right click
    };
}

void InputManager::Update(){
    // update the digital keys
    IOKey* current_key;
    for (auto i = digital_keys_.begin(); i != digital_keys_.end(); i++) {
        current_key = i->second;
        current_key->Update();
    }

    // update the analog axis
    AnalogAxis* current_analog_axis;
    for (auto i = analog_axis_.begin(); i != analog_axis_.end(); i++) {
        current_analog_axis = i->second;
        current_analog_axis->Update();
    };
}


bool InputManager::KeyIsPressed(std::string key){
    return digital_keys_.at(key)->is_pressed_;
}


bool InputManager::KeyGotPressed(std::string key){
    return digital_keys_.at(key)->got_pressed_;
}


bool InputManager::KeyGotReleased(std::string key){
    return digital_keys_.at(key)->got_released_;
}


int InputManager::GetAnalogAxisValue(std::string key){
    return analog_axis_.at(key)->value_;
}


int InputManager::GetLastAnalogAxisValue(std::string key){
    return analog_axis_.at(key)->last_value_;
}


int InputManager::GetDeltaAnalogAxisValue(std::string key){
    return analog_axis_.at(key)->last_value_;
}
