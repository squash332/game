#pragma once
#include "raylib.h"
#include "Constants.hpp"
#include <string>

inline Vector2 getScreenCenter()
{
    return { VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f };
}

inline Rectangle centerRectOnScreen(float width, float height)
{
    return {
        (VIRTUAL_WIDTH - width) / 2.0f,
        (VIRTUAL_HEIGHT - height) / 2.0f,
        width,
        height
    };
}

inline Rectangle centerRectInRect(Rectangle outer, float innerWidth, float innerHeight)
{
    return {
        outer.x + (outer.width - innerWidth) / 2.0f,
        outer.y + (outer.height - innerHeight) / 2.0f,
        innerWidth,
        innerHeight
    };
}