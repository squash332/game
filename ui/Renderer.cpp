#include "Renderer.hpp"
#include <cmath>

Renderer::Renderer()
{
    player_sprite_ = LoadTexture("res/me1.png");
}

Renderer::~Renderer()
{
    UnloadTexture(player_sprite_);
}

void Renderer::drawPlayer(const Player &player)
{
    DrawTextureV(player_sprite_, {floorf(player.getX()), floorf(player.getY())}, RAYWHITE);
}

void Renderer::drawMap(const Map &m)
{
    for (const TileLayer &layer : m.getTileLayers())
    {
        for (const Tile &tile : layer.tiles)
        {
            if (tile.id == 0)
                continue;

            Vector2 position = {(float)(tile.x * TILE_SIZE), (float)(tile.y * TILE_SIZE)};
            DrawTextureRec(tile.texture, tile.rectangle, position, WHITE);
        }
    }
}

void Renderer::displayLogs()
{
    DrawFPS(0, 0);
}