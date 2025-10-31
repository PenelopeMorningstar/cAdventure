#pragma once

#include "common.hpp"


class TimeManager
{
    public:
        const float ONE_MILLISECOND_ = 0.001;
        const float IDEAL_FPS_ = 60.0;
        const float IDEAL_FRAME_LENGTH_ = 1 / IDEAL_FPS_;

        float previous_tick_;
        float current_tick_;
        float fps_;
        float delta_time_;

        float GetTime();
        TimeManager();
        void Update();
    private:
};
