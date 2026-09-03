#pragma once

#include "Map.hpp"
#include "Entity.hpp"

namespace collision
{
    bool isTileWalkable(Rectangle givenPos, const Map &map);
    bool isInMeleeRange(const Entity &other1, const Entity &other2);
} // collision