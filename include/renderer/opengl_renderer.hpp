#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "common.hpp"
#include "renderer/abstract_renderer.hpp"

class OpenGLRenderer : public AbstractRenderer
{
    public:
        bool ConfigureDisplay();
        void Exit();
        bool CreateDisplay();
        void DrawRect(int left, int top, int width, int height);
        void DrawRect(int left, int top, int width, int height, float rotation);
        void Update();
    private:
        std::string display_title_ = "Test";
        int screen_width_ = 800;
        int screen_height_ = 600;
        glm::mat4 projection_;
        GLFWwindow* window_;

        unsigned int rect_vao_;
        unsigned int rect_vbo_;
        unsigned int rect_ebo_;
};