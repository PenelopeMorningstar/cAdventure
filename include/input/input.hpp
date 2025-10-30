#pragma once

#include "input/analog_axis.hpp"
#include "input/io_key.hpp"


#include <unordered_map>
#include <string>


class InputManager
{
    public:
        std::unordered_map<std::string, IOKey*> keys = {
            {"left", new IOKey(41)},
            {"right", new IOKey(44)},
            {"up", new IOKey(57)},
            {"down", new IOKey(53)}
        };

        void UpdateKeys();

    private:
};
