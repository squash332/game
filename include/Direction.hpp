#pragma once

enum class Direction
{
    None = 0,
    Up = 1 << 0,    // 1
    Down = 1 << 1,  // 2
    Left = 1 << 2,  // 4
    Right = 1 << 3, // 8

    TopLeft = Up | Left,    // 5
    TopRight = Up | Right,  // 9
    BotLeft = Down | Left,  // 6
    BotRight = Down | Right // 10

};

inline Direction operator|(const Direction a, const Direction b)
{
    return static_cast<Direction>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

inline bool operator&(const Direction a, const Direction b)
{
    return (static_cast<unsigned char>(a) & static_cast<unsigned char>(b)) != 0;
}
