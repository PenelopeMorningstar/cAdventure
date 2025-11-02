#include "renderer/texture_manager.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void TextureManager::RegisterTexture(std::string key, std::string src){
    int width, height, n_channels;
    unsigned char* data = stbi_load(src.c_str(), &width, &height, &n_channels, 0);
    textures_[key] = {data, width, height, n_channels, 0};
    g_render->InitTexture(&textures_.at(key));

}


Texture& TextureManager::GetTexture(std::string key){
    return textures_.at(key);
}