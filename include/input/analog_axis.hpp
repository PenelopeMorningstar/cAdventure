#pragma once

#include "common.hpp"

class AnalogAxis
{
    public:
        const int CURSOR_X_KEY_CODE_ = 1;
        const int CURSOR_Y_KEY_CODE_ = 2;
        int key_code_;

        int value_ = 0;
        int last_value_ = 0;
        int delta_ = 0;

        AnalogAxis(int key_code);
        void Update();
    private:
};
