#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "common.hpp"
#include "renderer/abstract_renderer.hpp"

class IOKey
{
    public:
        int key_code_ = 0;
        bool is_pressed_ = false;
        bool got_pressed_ = false;
        bool got_released_ = false;
    
        IOKey(int key_code);
        void Update();
    private:
};
