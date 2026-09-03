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

inline void drawCenteredText(const std::string &text, Rectangle bounds, int fontSize, Color color)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - fontSize) / 2.0f;
    DrawText(text.c_str(), (int)textX, (int)textY, fontSize, color);
}