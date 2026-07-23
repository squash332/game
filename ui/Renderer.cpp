#include "Renderer.hpp"
#include <cmath>

Renderer::Renderer()
{
    player_sprite_ = LoadTexture("res/fire-dragon.png");
    enemy_knight_ = LoadTexture("res/enemy_knight.png");
    frame_width_ = player_sprite_.width / NR_OF_FRAMES_IN_TEXTURE;
}

Renderer::~Renderer()
{
    UnloadTexture(player_sprite_);
    UnloadTexture(enemy_knight_);
}

void Renderer::drawPlayer(const Player &player)
{
    DrawTextureRec(player_sprite_, Rectangle{
        (frame_width_ * player.frame_number_),
        0,
        player_sprite_.width/NR_OF_FRAMES_IN_TEXTURE,
        player_sprite_.height},
        {floorf(player.getX()), floorf(player.getY())},
        RAYWHITE
        );
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

void Renderer::drawEnemy(const Enemy &enemy)
{
    DrawTextureRec(enemy_knight_,
                   Rectangle{0, 0, enemy_knight_.width / NR_OF_FRAMES_IN_TEXTURE, enemy_knight_.height}, {floorf(enemy.getX()), floorf(enemy.getY())}, RAYWHITE);
}
