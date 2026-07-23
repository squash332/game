#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Map.hpp"

class Renderer
{
public:
    Renderer();
    Renderer(const Renderer &other) = delete;
    ~Renderer();

    void drawPlayer(const Player &other);
    void drawMap(const Map &other);

    
protected:
private:
    Texture2D player_sprite_;
    float frame_width_;
};