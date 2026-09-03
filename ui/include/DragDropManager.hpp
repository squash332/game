#pragma once
#include "raylib.h"
#include "Mouse.hpp"

struct DragState
{
    bool active = false;
    void *dragged_item = nullptr;
    Vector2 drag_offset = {0, 0};
    Vector2 current_pos = {0, 0};

    // 
    void start(void* item, Vector2 itemPos)
    {
        active = true;
        dragged_item = item;
        drag_offset = {mouse.x - itemPos.x, mouse.y - itemPos.y};

        current_pos = itemPos;

    }

    void update()
    {
        if (!active) return;
        current_pos = {mouse.x - drag_offset.x, mouse.y - drag_offset.y};

    }

    void *end()
    {
        active = false;
        void* item = dragged_item;
        dragged_item = nullptr;
        return item;

    }
};
