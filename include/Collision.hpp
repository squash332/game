#pragma once

#include "Map.hpp"

namespace collision {
    bool isTileWalkable(Rectangle givenPos, const Map &map);
} // collision