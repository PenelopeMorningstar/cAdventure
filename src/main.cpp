#include "common.hpp"
#include "renderer/opengl_renderer.hpp"


int main() {
    g_render->ConfigureDisplay();

    // objects have been created; entering game loop
    while (g_game_manager->is_running_) {
        g_render->Update();
    }
}
