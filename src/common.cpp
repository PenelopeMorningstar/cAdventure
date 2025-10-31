#include "common.hpp"



// create a game manager
GameManager* g_game_manager = new GameManager();

// create a render object
AbstractRenderer* g_render;

InputManager* g_input_manager = new InputManager();

AudioManager* g_audio_manager = new AudioManager();

TimeManager* g_time_manager = new TimeManager();

TextureManager* g_texture_manager = new TextureManager();


void print_float(float my_float){
    std::cout.precision(20);
    std::cout << std::setw(20) << my_float << "\n";
}
