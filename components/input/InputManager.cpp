#include "InputManager.hpp"

#include "raylib.h"

void InputManager::bindHeld(int key, std::function<void()> action)
{
  held_keybinds_[key] = action;
}

void InputManager::bindPressed(int key, std::function<void()> action)
{
  pressed_keybinds_[key] = action;
}

void InputManager::update()
{
  for (auto const &[key, action] : held_keybinds_)
  {
    if (IsKeyDown(key))
    {
      action();
    }
  }
  for (auto const &[key, action] : pressed_keybinds_)
  {
    if (IsKeyPressed(key))
    {
      action();
    }
  }
}