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
#include "HUD.hpp"
#include "Collision.hpp"
#include "ActionBar.hpp"
#include "PositioningUtilites.hpp"

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
  void handleTargetClick();
  void tryMove();
  Vector2 getVirtualMousePos();
  void updateEnemies();
  void updateTargetRange();
  void tryAttack();

  void handleDebugMode(); // open with 'T' keybind
  void handleEscapeKey();

  // HUD relevant 
  void handleMenuClick();
  bool drawn_menu;
  bool in_edit_mode;
  void cachePositions();
  void updateEditMode();
  void drawEditMode();
  void endEditMode(bool save);

  Vector2 mouseScreen;


  Entity *current_target = nullptr;
  Entity *focus_target = nullptr;

private:
  Window game_window_;
  InputManager input_;
  Player player_;
  Map map_;
  Renderer renderer_;
  Cam2d cam_;
  HUD hud_;
  ActionBar action_bar_;

  Rectangle cached_player_frame_;
  Rectangle cached_target_frame_;
  Rectangle cached_focus_frame_;

  Button save_btn_;
  Button discard_btn_;

  std::vector<std::unique_ptr<Enemy>> enemies_;

  float timer = 0.0f;
  float delta_time = 0.0f;
  int frame = 0;
};