#pragma once 

#include "Ability.hpp"

struct Slot
{
    Ability* ability = nullptr;
    Keybind keybind{};
    float size = ABILITY_ICON_SIZE;

    bool empty() const
    {
        return ability == nullptr;
    }
};