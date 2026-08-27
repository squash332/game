#pragma once

#include "Map.hpp"

struct CircleHitbox
{
    Vector2 center;
    float radius;
};

namespace collision
{
    bool isTileWalkable(Rectangle givenPos, const Map &map);
    bool isMeleeRange(CircleHitbox hitbox1, CircleHitbox hitbox2);
} // collision