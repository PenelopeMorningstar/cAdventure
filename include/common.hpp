#include <string>
#pragma once

#include "game_manager.hpp"
#include "renderer/abstract_renderer.hpp"
#include "audio/audio.hpp"
#include "input/input.hpp"
#include "time/time.hpp"

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

extern GameManager* g_game_manager;
extern AbstractRenderer* g_render;
extern AudioManager* g_audio_manager;
extern InputManager* g_input_manager;
extern TimeManager* g_time_manager;

