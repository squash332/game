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
    DrawTextureRec(player_sprite_, Rectangle{(frame_width_ * player.frame_number_), 0, player_sprite_.width / NR_OF_FRAMES_IN_TEXTURE, player_sprite_.height},
                   {floorf(player.getX()), floorf(player.getY())},
                   RAYWHITE);
}

void Renderer::drawMap(const Map &m)
{
    for (const TileLayer &layer : m.getTileLayers())
    {
        for (const Tile &tile : layer.tiles)
        {
            if (tile.id == 0)
                continue;

            Vector2 position = {(floorf(tile.x * TILE_SIZE)), (floorf(tile.y * TILE_SIZE))};
            DrawTextureRec(tile.texture, tile.rectangle, position, WHITE);
        }
    }
}

void Renderer::drawEnemy(const Enemy &enemy)
{
    DrawTextureRec(enemy_knight_,
                   Rectangle{0, 0, enemy_knight_.width / NR_OF_FRAMES_IN_TEXTURE, enemy_knight_.height}, {floorf(enemy.getX()), floorf(enemy.getY())}, RAYWHITE);
}

void Renderer::drawNameplate(const Entity &entity, bool isTargeted)
{
    float barWidth = TILE_SIZE;
    float barHeight = 3.0f;
    Vector2 barPos = {floorf(entity.getX()), floorf(entity.getY() + 3.0f)};

    DrawRectangleV(barPos, {barWidth, barHeight}, DARKGRAY);

    float ratio = (float)entity.getCurrentHealth() / (float)entity.getMaxHealth();
    DrawRectangleV(barPos, {barWidth * ratio, barHeight}, RED);

    if (isTargeted)
    {
        DrawRectangleLines(barPos.x - 1, barPos.y - 1, barWidth + 2, barHeight + 2, YELLOW);
    }
}
