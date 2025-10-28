#include "renderer/opengl_renderer.hpp"

bool OpenGLRenderer::ConfigureDisplay(){
    display_title = "OpenGl Window Yay UwU";
    width = 800;
    height = 600;
    // // true = success; false = failure
    // if (!glfwInit()) return false;
    // GLFWwindow* window = glfwCreateWindow(width, height, display_title.c_str(), nullptr, nullptr);
    // projection = glm::ortho(0.0, (float)width, 0.0, height, -1.0, 1.0);
    // if (!window) return false;
    // glfwMakeContextCurrent(window);
    // glewInit();
    return true;
}

bool OpenGLRenderer::CreateDisplay(){
    // true = success; false = failure
    return true;
}

void OpenGLRenderer::DrawRect(int left, int top, int width, int height){


}
void OpenGLRenderer::DrawRect(int left, int top, int width, int height, float rotation){


}