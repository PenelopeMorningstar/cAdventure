#pragma once

class AbstractRenderer
{
    public:
        virtual bool ConfigureDisplay() = 0;
        virtual bool CreateDisplay() = 0;
        virtual void DrawRect(int left, int top, int width, int height) = 0;
        virtual void DrawRect(int left, int top, int width, int height, float rotation) = 0;
    private:
};