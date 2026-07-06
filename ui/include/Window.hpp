#pragma once

#include "raylib.h"

#include "Constants.hpp"

class Window
{
public:
    Window();
    Window(const Window &other) = delete; // no copying allowed
    ~Window();

    void beginFrame();
    void endFrame();
    bool shouldClose();
    void toggleFullscreen();

protected:
private:
    RenderTexture2D target_;
    bool fullscreen_ = false;
};