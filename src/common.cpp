#include "common.hpp"
#include "renderer/opengl_renderer.hpp"

// create a game manager
GameManager* g_game_manager = new GameManager();

// create a render object
AbstractRenderer* g_render = new OpenGLRenderer();