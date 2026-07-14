#include "Renderer.hpp"
#include <cmath>

Renderer::Renderer()
{
    player_sprite_ = LoadTexture("res/me1.png");
    map_ = LoadTexture("res/mainlevbuild.png");
}

Renderer::~Renderer()
{
    UnloadTexture(player_sprite_);
    UnloadTexture(map_);
}

void Renderer::drawPlayer(const Player &player)
{
    DrawTexture(player_sprite_, player.getX(), player.getY(), RAYWHITE);
}

void Renderer::drawMap(const Map &m)
{
}