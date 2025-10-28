#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "common.hpp"
#include "renderer/abstract_renderer.hpp"

class OpenGLRenderer : public AbstractRenderer
{
    public:
        std::string display_title;
        int width;
        int height;
        GLFWwindow* window;
        glm::mat4 projection;

        bool ConfigureDisplay();
        bool CreateDisplay();
        void DrawRect(int left, int top, int width, int height);
        void DrawRect(int left, int top, int width, int height, float rotation);
    private:
};