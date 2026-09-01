#pragma once

#include <cmath>

enum class Direction
{
    None = 0,
    Up = 1 << 0,    // 1
    Down = 1 << 1,  // 2
    Left = 1 << 2,  // 4
    Right = 1 << 3, // 8

};

inline Direction operator|(const Direction a, const Direction b)
{
    return static_cast<Direction>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

inline bool operator&(const Direction a, const Direction b)
{
    return (static_cast<unsigned char>(a) & static_cast<unsigned char>(b)) != 0;
}

inline Direction getDirectionToTarget(float player_x, float player_y, float target_x, float target_y) {
    float dx = target_x - player_x;
    float dy = target_y - player_y;

    if(fabs(dx) > fabs(dy))  {
        return dx > 0 ? Direction::Right : Direction::Left;
    }
    else {
        return dy > 0 ? Direction::Down : Direction::Up;
    }

}
