#pragma once

#include "common.hpp"
#include "stb_image.h"
#include <unordered_map>

struct Texture;

class TextureManager{
    public:
        void RegisterTexture(std::string key, std::string src);
        Texture& GetTexture(std::string key);
    
    private:
        std::unordered_map<std::string, Texture> textures_;
    
};