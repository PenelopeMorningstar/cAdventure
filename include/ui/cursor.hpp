#pragma once

#include "common.hpp"

class CursorManager
{
    public:
        // controls
        bool left_click_ = false;
        bool right_click_ = false;
        int x_pos_ = 0;
        int y_pos_ = 0;

        CursorManager();
        void Update();
        bool GetLeftClick();
        bool GetRightClick();
        int GetXPos();
        int GetYPos();
    private:
};