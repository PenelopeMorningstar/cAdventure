#include "renderer/opengl_renderer.hpp"

#include <iostream>
#include <iomanip>


int main() {
    g_render = new OpenGLRenderer();
    g_render->ConfigureDisplay();

    g_texture_manager->RegisterTexture("white","img/white.png");
    g_texture_manager->RegisterTexture("pumpkin","img/pumpkin.png");

    // objects have been created; entering game loop
    RectTransform t = {10,10,100,100};
    Color c = {1.0,1.0,1.0,1.0};
    RectTransform r2 = {110,10,200,100};

    while (g_game_manager->is_running_) {
        g_render->DrawRect(t, c, &g_texture_manager->GetTexture("pumpkin"), 0.0f);
        g_render->DrawRect(r2, c, &g_texture_manager->GetTexture("white"), 45.0f);


        print_float(g_time_manager->fps_);

        g_time_manager->Update();
        g_input_manager->Update();
        g_render->Update();
    }
}
