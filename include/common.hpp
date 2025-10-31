#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include <string>
#include <stdio.h>

#include "game_manager.hpp"
#include "renderer/abstract_renderer.hpp"
#include "audio/audio.hpp"
#include "input/input.hpp"
#include "time/time.hpp"
#include "renderer/texture_manager.hpp"

// used for printing
#include <iostream>
#include <iomanip>

struct Texture {
    unsigned char* data;
    int width;
    int height;
    int n_channels;
    unsigned int texture_id;
};

struct Color
{
    float r,g,b,a;
};

struct RectTransform{
    int l,t,w,h;
};

class GameManager;
class AbstractRenderer;
class AudioManager;
class InputManager;
class TimeManager;
class TextureManager;

extern GameManager* g_game_manager;
extern AbstractRenderer* g_render;
extern AudioManager* g_audio_manager;
extern InputManager* g_input_manager;
extern TimeManager* g_time_manager;
extern TextureManager* g_texture_manager;


void print_float(float my_float);
