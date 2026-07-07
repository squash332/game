#pragma once

#include "raylib.h"
#include "Player.hpp"

class Renderer
{
public:
    Renderer();
    Renderer(const Renderer &other) = delete;
    ~Renderer();

    void drawPlayer(const Player &other);

protected:
private:
    Texture2D player_sprite_;
};