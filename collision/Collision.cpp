#include "Collision.hpp"

#include <cmath>

bool collision::isTileWalkable(Rectangle givenPos, const Map &map) {
    int startCol = (int)floorf(givenPos.x / TILE_SIZE);
    int endCol   = (int)floorf((givenPos.x + givenPos.width) / TILE_SIZE);
    int startRow = (int)floorf(givenPos.y / TILE_SIZE);
    int endRow   = (int)floorf((givenPos.y + givenPos.height) / TILE_SIZE);

    std::cout << "range: col " << startCol << "-" << endCol << ", row " << startRow << "-" << endRow << std::endl;

    for (int y = startRow; y <= endRow; y++)
    {
        for (int x = startCol; x <= endCol; x++)
        {
            std::cout << "checking (" << x << "," << y << ")" << std::endl;
            if (!map.isWalkable(x, y))
            {
                std::cout << "BLOCKED at (" << x << "," << y << ")" << std::endl;
                return false;
            }
        }
    }
    return true;
}