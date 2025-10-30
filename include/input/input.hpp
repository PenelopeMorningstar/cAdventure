#pragma once

#include "common.hpp"
#include "input/analog_axis.hpp"


#include <unordered_map>
#include <string>

class IOKey;

class InputManager
{
    public:
        std::unordered_map<std::string, IOKey*> keys_;
        InputManager();

        void Update();
        bool KeyIsPressed(std::string key);
        bool KeyGotPressed(std::string key);
        bool KeyGotReleased(std::string key);

    private:
};
