#pragma once

class IOKey
{
    public:
        int key_code_ = 0;
        bool is_pressed_ = false;
        bool got_pressed_ = false;
        bool got_released_ = false;
    
        IOKey(int key_code);
        void Update(bool new_value);
    private:
};
