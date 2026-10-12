#pragma once

#include "raylib.h"
#include <cmath>

inline void drawRectSnapped(Rectangle r, Color c)
{
    DrawRectangle((int)floorf(r.x), (int)floorf(r.y),
                  (int)floorf(r.width), (int)floorf(r.height), c);
}

inline void drawTextureSnapped(Texture2D tex, Vector2 pos, Color c)
{
    DrawTextureV(tex, { floorf(pos.x), floorf(pos.y) }, c);
}

// instead of flooring everything, dont forget to refactor all of the calls that use flooring, for drawing, to improve 
// code readability. Swap all calls that floor and add functions if necessary