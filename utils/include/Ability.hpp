#pragma once 

#include "raylib.h"
#include <string>
#include <memory>
#include <vector>

#include "Constants.hpp"

enum class AbilityAnim { Slash, Clap };

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
    AbilityAnim animType = AbilityAnim::Slash;
    float cooldown_remaining = 0.0f;
};

inline std::string keyToString(int key)
{
    // letters and numbers (a-z, 0-9) mapped to ascii
    if (key >= KEY_A && key <= KEY_Z)
        return std::string(1, (char)key);

        return std::string(1, (char)key);

    // these special keys are needed for special labels
    switch (key)
    {
        case KEY_SPACE:       return "Space";
        case KEY_LEFT_SHIFT:  return "Shift";
        case KEY_RIGHT_SHIFT: return "Shift";
        case KEY_LEFT_CONTROL:  return "Ctrl";
        case KEY_RIGHT_CONTROL: return "Ctrl";
        case KEY_TAB:         return "Tab";
        case KEY_F1:          return "F1";
        case KEY_F2:          return "F2";
        case KEY_F3:          return "F3";
        case KEY_F4:          return "F4";
        // .. add more when u need
        default:              return "?";
    }
}

inline std::string keybindToString(const Keybind &bind)
{
    std::string result;
    if (bind.ctrl)  result += "Ctrl+";
    if (bind.shift) result += "Shift+";
    if (bind.alt)   result += "Alt+";
    result += keyToString(bind.key);
    return result;
}
