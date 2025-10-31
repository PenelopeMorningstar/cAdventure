#pragma once
#include "common.hpp"

struct RectTransform;
struct Color;
struct Texture;

class AbstractRenderer
{
    public:
        virtual bool ConfigureDisplay() = 0;
        virtual bool CreateDisplay() = 0;
        virtual void DrawRect(RectTransform& transform, Color& color) = 0;
        virtual void DrawRect(RectTransform& transform, Color& color, Texture* texture) = 0;
        virtual void DrawRect(RectTransform& transform, Color& color, Texture* texture, float rotation) = 0;
        virtual void DrawRect(RectTransform& transform, Color& color, float rotation) = 0;
        virtual void InitTexture(Texture* texture) = 0;
        virtual void Update() = 0;
        GLFWwindow* window_;
    private:
};