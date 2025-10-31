#include "time/time.hpp"
#include <iostream>
#include <chrono>
#include <thread>


float TimeManager::GetTime(){
    // gets the time in seconds since the program started being executed
    return clock() / 1000.0;
}


TimeManager::TimeManager(){
    current_tick_ = g_time_manager->GetTime();
    previous_tick_ = current_tick_ - IDEAL_FRAME_LENGTH_;
    fps_ = IDEAL_FPS_;
    delta_time_ = (current_tick_ - previous_tick_) / 1000;
}


void TimeManager::Update(){
    // get the time needed to complete the frame
    previous_tick_ = current_tick_;
    current_tick_ = g_time_manager->GetTime();
    delta_time_ = (current_tick_ - previous_tick_) / 1000;

    // wait if there's too much time until the next frame should appear
    while (delta_time_ < (IDEAL_FRAME_LENGTH_ - ONE_MILLISECOND_)){
        current_tick_ = g_time_manager->GetTime();
        delta_time_ = (current_tick_ - previous_tick_);
    }

    // update the fps
    fps_ = 1 / delta_time_;
}
