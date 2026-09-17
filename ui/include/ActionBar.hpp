#pragma once

#include "Constants.hpp"
#include "DragDropManager.hpp"
#include "Player.hpp"
#include "Mouse.hpp"
#include "Settings.hpp"
#include "Ability.hpp"

#include "raylib.h"

struct Slot
{
    std::optional<Ability> ability;
    Keybind keybind;
    float size = ABILITY_ICON_SIZE;

    bool empty() const
    {
        return !ability.has_value();
    }
};

class ActionBar
{
public:
    ActionBar();
    ~ActionBar() = default;

    void buildDefaultActionBar();
    void draw(const Player &player);
    void handleBarClick();
    void handleDrag();
    void updateEditModeComponents();
    int handleAbilitySwap(Player &player);

    void setActionBarPos(Rectangle pos);

    int getHoveredSlot(size_t abilityCount) const;
    Rectangle getActionBar() const;
    Rectangle getSlotBounds(int index) const;
    Keybind getSlotKeybind(int index) const;

private:
    void drawCooldown(Rectangle rec, const Ability &ability, int index);
    void drawKeybind(Rectangle rec, int index);

private:
    Rectangle action_bar_;
    Vector2 position_;
    int rows_;
    int cols_;
    float iconPadding_;
    int grabbed_slot_;
    std::vector<Slot> slots_;
};