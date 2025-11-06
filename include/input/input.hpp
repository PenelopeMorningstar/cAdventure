#pragma once

#include "common.hpp"


#include <unordered_map>
#include <string>

class IOKey;
class AnalogAxis;

class InputManager
{
    public:
        std::unordered_map<std::string, IOKey*> digital_keys_;
        std::unordered_map<std::string, AnalogAxis*> analog_axis_;
        InputManager();

        void Update();

        // get a digital key
        bool KeyIsPressed(std::string key);
        bool KeyGotPressed(std::string key);
        bool KeyGotReleased(std::string key);

        // get an analog axis value
        int GetAnalogAxisValue(std::string key);
        int GetLastAnalogAxisValue(std::string key);
        int GetDeltaAnalogAxisValue(std::string key);

    private:
};
