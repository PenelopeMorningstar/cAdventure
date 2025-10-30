#include "input/input.hpp"
#include "input/io_key.hpp"

InputManager::InputManager() {
    keys_ = {
        {"left", new IOKey(0x41)},
        {"right", new IOKey(0x44)},
        {"up", new IOKey(0x57)},
        {"down", new IOKey(0x53)}
    };
}

void InputManager::Update(){
    IOKey* current_key;
    for (auto i = keys_.begin(); i != keys_.end(); i++) {
        current_key = i->second;
        current_key->Update();
    }
}


bool InputManager::KeyIsPressed(std::string key){
    return keys_.at(key)->is_pressed_;
}


bool InputManager::KeyGotPressed(std::string key){
    return keys_.at(key)->got_pressed_;
}


bool InputManager::KeyGotReleased(std::string key){
    return keys_.at(key)->got_released_;
}
