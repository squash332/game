#pragma once

#include "raylib.h"
#include <cmath>

inline void drawRectangleFloored(Rectangle r, Color c)
{
    DrawRectangle((int)floorf(r.x), (int)floorf(r.y),
                  (int)floorf(r.width), (int)floorf(r.height), c);
}

inline void drawTextureFloored(Texture2D tex, Vector2 pos, Color c)
{
    DrawTextureV(tex, {floorf(pos.x), floorf(pos.y)}, c);
}

inline void drawCenteredTextFloored(const std::string &text, Rectangle bounds, int fontSize, Color c)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - fontSize) / 2.0f;
    DrawText(text.c_str(), (int)floorf(textX), (int)floorf(textY), fontSize, c);
}

inline void DrawRectangleVFloored(Vector2 pos, Vector2 size, Color c)
{
    DrawRectangleV({floorf(pos.x), floorf(pos.y)}, {floorf(size.x), floorf(size.y)}, c);
}

inline void drawRectangleLinesExFloored(Rectangle r, float lineThick, Color c)
{
    DrawRectangleLinesEx({floorf(r.x),floorf(r.y),floorf(r.width),floorf(r.height)},lineThick, c);
}
// instead of flooring everything, dont forget to refactor all of the calls that use flooring, for drawing, to improve
// code readability. Swap all calls that floor and add functions if necessary