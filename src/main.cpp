#include "renderer/opengl_renderer.hpp"


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
        g_input_manager->Update();
        bool left = g_input_manager->KeyIsPressed("left");
        bool right = g_input_manager->KeyIsPressed("right");
        bool up = g_input_manager->KeyIsPressed("up");
        bool down = g_input_manager->KeyIsPressed("down");
        if(left){
            printf("left!");
        }
        if(right){
            t.l += 1;
            printf("right!");
        }
        if(up){
            printf("up!");
        }
        if(down){
            printf("down!");
        }

        g_render->Update();
    }
}
