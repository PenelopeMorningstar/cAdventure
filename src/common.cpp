#include "common.hpp"



// create a game manager
GameManager* g_game_manager = new GameManager();

// create a render object
AbstractRenderer* g_render;

CursorManager* g_cursor_manager = new CursorManager();

InputManager* g_input_manager = new InputManager();

AudioManager* g_audio_manager = new AudioManager();

TimeManager* g_time_manager = new TimeManager();

TextureManager* g_texture_manager = new TextureManager();
