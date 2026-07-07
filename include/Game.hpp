#pragma once

#include <memory>
#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Player.hpp"
#include "Renderer.hpp"


enum class GameState
{
//   MainMenu,
//   Playing,
//   Pause,
//   Dialogue,
//   Transition
};

class Game
{
public:
  Game();
  Game(const Game& other) = delete; // no multiple game instances
  ~Game() = default;
  void run();


private:
  Texture2D sprite;

  std::unique_ptr<Window> game_window_;
  std::unique_ptr<InputManager> input_;
  std::unique_ptr<Player> player_;
  std::unique_ptr<Renderer> renderer_;
};