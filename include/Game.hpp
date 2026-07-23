#pragma once

#include <memory>
#include <iostream>

#include "raylib.h"

#include "Constants.hpp"
#include "InputManager.hpp"
#include "Window.hpp"
#include "Player.hpp"
#include "Renderer.hpp"
#include "Map.hpp"
#include "Camera.hpp"
#include "Enemy.hpp"

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
  Game(const Game &other) = delete; // no multiple game instances
  ~Game() = default;
  void run();

  void toggleDebugMode();
  void displayLogs();
  bool debug_mode = false;

private:

  Window game_window_;
  InputManager input_;
  Player player_;
  Map map_;
  Renderer renderer_;
  Cam2d cam_;

  std::vector<std::unique_ptr<Enemy>> enemies_;

  float timer, delta_time = 0.0f;
  int frame = 0;
};