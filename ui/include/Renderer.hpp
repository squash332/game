#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Map.hpp"
#include "Enemy.hpp"

class Renderer
{
public:
    Renderer();
    Renderer(const Renderer &other) = delete;
    ~Renderer();

    void drawPlayer(const Player &other);
    void drawMap(const Map &other);
    void drawEnemy(const Enemy &other);
    
protected:
private:
    Texture2D player_sprite_;
    Texture2D enemy_knight_;
    float frame_width_;
};