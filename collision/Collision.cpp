#include "Collision.hpp"

#include <cmath>

bool collision::isTileWalkable(Rectangle givenPos, const Map &map) {
    int startCol = (int)floorf(givenPos.x / TILE_SIZE);
    int endCol   = (int)floorf((givenPos.x + givenPos.width) / TILE_SIZE);
    int startRow = (int)floorf(givenPos.y / TILE_SIZE);
    int endRow   = (int)floorf((givenPos.y + givenPos.height) / TILE_SIZE);

    // std::cout << "range: col " << startCol << "-" << endCol << ", row " << startRow << "-" << endRow << std::endl;

    for (int y = startRow; y <= endRow; y++)
    {
        for (int x = startCol; x <= endCol; x++)
        {
            // std::cout << "checking (" << x << "," << y << ")" << std::endl;
            if (!map.isWalkable(x, y))
            {
                // std::cout << "BLOCKED at (" << x << "," << y << ")" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool collision::isMeleeRange(CircleHitbox hitbox1, CircleHitbox hitbox2)
{
    // TODO: hitboxes for taking damage from projectiles etc will stay rectangles, need to be made smaller
    // make another circle for a default melee range which every melee shares
    // make enemies hitboxes for taking damage circles which will be checked with everything else 
    // alongside player's melee range for taking damage
    // reason : simplify melee abilities
    // make UI icons display cooldown and maybe some text.
    // add ground spikes for testing player hitbox and feel for the game
    return false;
}
