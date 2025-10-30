#include "common.hpp"



// create a game manager
GameManager* g_game_manager = new GameManager();

// create a render object
AbstractRenderer* g_render;

InputManager* g_input_manager = new InputManager();

AudioManager* g_audio_manager = new AudioManager();

TimeManager* g_time_manager = new TimeManager();