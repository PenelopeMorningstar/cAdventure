#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <stdio.h>
#include <unordered_map>
#include <vector>

#include "common.hpp"
#include "renderer/abstract_renderer.hpp"

struct ColoredRectCall{
    RectTransform transform;
    Color color;
    float rotation;
};

class OpenGLRenderer : public AbstractRenderer
{
    public:
        bool ConfigureDisplay();
        void Exit();
        bool CreateDisplay();
        void DrawRect(RectTransform& transform, Color& color);
        void DrawRect(RectTransform& transform, Color& color, float rotation);
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
        unsigned int colored_rect_program;
        unsigned int colored_rect_projection_i;
        unsigned int colored_rect_ltwh_i;
        unsigned int colored_rect_color_i;
        unsigned int colored_rect_rotation_i;
        std::vector<ColoredRectCall> colored_rects = {};
};