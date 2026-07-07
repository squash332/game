#include "Renderer.hpp"

Renderer::Renderer()
{
    player_sprite_ = LoadTexture("res/me1.png");
}

Renderer::~Renderer()
{
    UnloadTexture(player_sprite_);
}

void Renderer::drawPlayer(const Player& player) {
    DrawTexture(player_sprite_, player.getX(), player.getY(), RAYWHITE);
}