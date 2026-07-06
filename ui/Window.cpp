#include "Window.hpp"

Window::Window()
{
  InitWindow(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, "Da Game");
  SetTargetFPS(60);
  target_ = LoadRenderTexture(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
}

Window::~Window()
{
  UnloadRenderTexture(target_);
  CloseWindow();
}

void Window::beginFrame()
{
  BeginTextureMode(target_);
}

void Window::endFrame()
{
  EndTextureMode();
  BeginDrawing();
  DrawTexturePro(
      target_.texture,
      Rectangle {0, 0, (float)VIRTUAL_WIDTH, -(float)VIRTUAL_HEIGHT},
      Rectangle {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()},
      Vector2 {0, 0},
      0.0f,
      WHITE);
  EndDrawing();
}

bool Window::shouldClose()
{
  if (WindowShouldClose()) {
    return true;
  }
  return false;
}

void Window::toggleFullscreen()
{
  ToggleFullscreen();
  if (!fullscreen_) {
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  } else {
    SetWindowSize(VIRTUAL_WIDTH, VIRTUAL_HEIGHT);
  }
  fullscreen_ = !fullscreen_;
}
