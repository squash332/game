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
    DrawTexture(player_sprite_, player.getX(), player.getY(), RAYWHITE);
}

void Renderer::drawMap(const Map &m)
{
    for (const TileLayer &layer : m.getTileLayers())
    {
        for (size_t i = 0; i < layer.tiles.size(); i++)
        {
            const Tile &tile = layer.tiles[i];
            if (tile.id == 0)
                continue;

            int col = i % layer.width;
            int row = i / layer.width;

            Vector2 position = {(float)(col * TILE_SIZE), (float)(row * TILE_SIZE)};
            DrawTextureRec(tile.texture, tile.rectangle, position, WHITE);
        }
    }
}