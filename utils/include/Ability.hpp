#pragma once 

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

#include "Constants.hpp"

struct Keybind {
    int key = KEY_NULL;
    bool shift = false;
    bool ctrl = false;
    bool alt = false;
};

struct Ability
{
    int id;
    std::string name;
    Texture2D icon;
    Vector2 iconSize = ABILITY_ICON_SIZE_VECTOR;
    std::string description;
    int damage = 0;
    float cooldown = 0.0f;
    Keybind keybinding;
};
