#pragma once

#include <functional>
#include <unordered_map>

class InputManager
{
public:
  void bindHeld(int key, std::function<void()>);
  void update();
  void bindPressed(int key, std::function<void()> action);

private:
  std::unordered_map<int, std::function<void()>> held_keybinds_;
  std::unordered_map<int, std::function<void()>> pressed_keybinds_;
};
