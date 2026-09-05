#pragma once 

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

struct Keybind {
    int key = KEY_NULL;
    bool shift = false;
    bool ctrl = false;
    bool alt = false;
};

struct Ability
{
    int id;
    Texture2D icon;
    Vector2 iconSize;
    std::string name;
    std::string description;
    int damage = 0;
    float cooldown = 0.0f;
    Keybind keybinding;
};
