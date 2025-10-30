#include "input/io_key.hpp"


IOKey::IOKey(int key_code): key_code_(key_code) {
    key_code_ = key_code;
}


void IOKey::Update(){
    if(!g_render->window_){
        return;
    }
    bool new_value = glfwGetKey(g_render->window_, key_code_);
    got_pressed_ = !is_pressed_ && new_value;
    got_released_ = is_pressed_ && !new_value;
    is_pressed_ = new_value;
}