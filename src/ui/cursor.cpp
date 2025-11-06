#include "ui/cursor.hpp"


CursorManager::CursorManager(){

}


void CursorManager::Update(){
    // get mouse clicks
    int left_click = glfwGetMouseButton(g_render->window_, GLFW_MOUSE_BUTTON_LEFT);
    int right_click = glfwGetMouseButton(g_render->window_, GLFW_MOUSE_BUTTON_RIGHT);
    left_click_ = left_click;
    right_click_ = right_click;

    // get current mouse position
    double x_pos, y_pos;
    glfwGetCursorPos(g_render->window_, &x_pos, &y_pos);
    x_pos_ = std::floor(x_pos);
    y_pos_ = std::floor(y_pos);
}


bool CursorManager::GetLeftClick(){
    return left_click_;
}


bool CursorManager::GetRightClick(){
    return right_click_;
}


int CursorManager::GetXPos(){
    return x_pos_;
}


int CursorManager::GetYPos(){
    return y_pos_;
}
