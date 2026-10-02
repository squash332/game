#pragma once

#include "Constants.hpp"
#include "DragDropManager.hpp"
#include "Player.hpp"
#include "Mouse.hpp"
#include "Settings.hpp"
#include "Ability.hpp"
#include "Slot.hpp"

#include "raylib.h"


class ActionBar
{
public:
    ActionBar( Player &player);
    ~ActionBar() = default;

    void startAbilityCooldown(Ability &ability);
    void updateCooldowns(float delta);
    void buildDefaultActionBar();
    void draw();
    void handleBarClick();
    void handleDrag();
    void updateEditModeComponents();
    int handleAbilitySwap(Player &player);
    void reArrangeSlots(int first, int second);

    void setActionBarPos(Rectangle pos);

    int getHoveredSlot() const;
    Rectangle getActionBar() const;
    Rectangle getSlotBounds(int index) const;
    Keybind getSlotKeybind(int index) const;
    const std::vector<Slot> getSlots() const;
    Ability* getAbility(int slotIndex);
    void setAbility(int slotIndex, Ability &ability);

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