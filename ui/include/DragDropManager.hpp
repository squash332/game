#pragma once
#include "raylib.h"

struct DragState
{
    bool active = false;
    void *dragged_item = nullptr;
    Vector2 drag_offset = {0, 0};
    Vector2 current_pos = {0, 0};

    // 
    void start(void* item, Vector2 mousePos, Vector2 itemPos)
    {
        active = true;
        dragged_item = item;
        drag_offset = {mousePos.x - itemPos.x, mousePos.y - itemPos.y};

        current_pos = itemPos;

    }

    void update(Vector2 mousePos)
    {
        if (!active) return;
        current_pos = {mousePos.x - drag_offset.x, mousePos.y - drag_offset.y};

    }

    void *end()
    {
        active = false;
        void* item = dragged_item;
        dragged_item = nullptr;
        return item;

    }
};
