#pragma once
#include "raylib.h"
#include "Constants.hpp"

inline Vector2 mouse = {0, 0};

inline void updateMouse()
{
    Vector2 raw = GetMousePosition();
    float scaleX = (float)VIRTUAL_WIDTH / GetScreenWidth();
    float scaleY = (float)VIRTUAL_HEIGHT / GetScreenHeight();
    mouse = { raw.x * scaleX, raw.y * scaleY };
}