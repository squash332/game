#include "InputManager.hpp"

#include "raylib.h"

void InputManager::bind(int key, std::function<void()> action)
{
  keybinds_[key] = action;
}

void InputManager::update()
{
  for (auto const& [key, action] : keybinds_) {
    if (IsKeyPressed(key)) {
      action();
    }
  }
}