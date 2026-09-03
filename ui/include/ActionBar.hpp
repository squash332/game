#pragma once

#include "Constants.hpp"
#include "DragDropManager.hpp"
#include "Player.hpp"
#include "Mouse.hpp"
#include "Settings.hpp"

#include "raylib.h"

class ActionBar
{
public:
    ActionBar();
    void draw(const Player &player);
    void handleBarClick();
    void handleDrag();
    void update();

    ~ActionBar() = default;

    Rectangle getActionBar() const;
    void setActionBarPos(Rectangle pos);

private:
    Rectangle action_bar_;
    Vector2 position_;
    int rows_;
    int cols_;
    float slotSize_;
    float iconPadding_;
    DragState drag_state_;
};