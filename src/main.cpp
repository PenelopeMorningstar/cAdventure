#include "renderer/opengl_renderer.hpp"

#include <iostream>
#include <iomanip>


int main() {
    g_render = new OpenGLRenderer();
    g_render->ConfigureDisplay();

    // objects have been created; entering game loop
    RectTransform t = {10,10,100,100};
    Color c = {1.0,0.0,0.0,1.0};
    RectTransform r2 = {110,10,100,100};

    while (g_game_manager->is_running_) {
        g_render->DrawRect(t, c, 0.0f);
        g_render->DrawRect(r2, c, 45.0f);


        print_float(g_time_manager->fps_);

        g_time_manager->Update();
        g_input_manager->Update();
        g_render->Update();
    }
}
