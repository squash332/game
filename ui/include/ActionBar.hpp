#pragma once

#include "Constants.hpp"
#include "Player.hpp"

#include "raylib.h"

class ActionBar
{
public:
    ActionBar();
    void draw(const Player &player);
    void handleDrag();
    void handleClick();

    ~ActionBar() = default;

    Rectangle getBounds() const;

private:
    Rectangle bounds_;
    Vector2 position_;
    int rows_;
    int cols_;
    float slotSize_;
    float iconPadding_;
};