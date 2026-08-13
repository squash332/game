#include "Renderer.hpp"
#include <cmath>

Renderer::Renderer()
{
    player_sprite_ = LoadTexture("res/Crusader.png");
    enemy_knight_ = LoadTexture("res/enemy_knight.png");
}

Renderer::~Renderer()
{
    UnloadTexture(player_sprite_);
    UnloadTexture(enemy_knight_);
}

void Renderer::drawPlayer(const Player &player)
{
    AnimationData anim = getAnimData(player.getAnimState());
    int wrappedFrame = player.frame_number_ % anim.frameCount;

    Rectangle src = {
        wrappedFrame * player.getSpriteWidth(),
        anim.row * player.getSpriteHeight(),
        player.getSpriteWidth(),
        player.getSpriteHeight()
    };

    DrawTextureRec(player_sprite_, src, { floorf(player.getX()), floorf(player.getY()) }, RAYWHITE);
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
    // 9 is for now a hard coded number of frames in the knight's png 
    DrawTextureRec(enemy_knight_,
                   Rectangle{0, 0, enemy_knight_.width / 9, enemy_knight_.height}, {floorf(enemy.getX()), floorf(enemy.getY())}, RAYWHITE);
}

void Renderer::drawNameplate(const Entity &entity, bool isTargeted)
{
    float barWidth = TILE_SIZE + TILE_SIZE / 2;
    float barHeight = SPRITE_HEIGHT % 10;
    float ratio = (float)entity.getCurrentHealth() / (float)entity.getMaxHealth();

    Vector2 barPos = {floorf(entity.getX()) + entity.getSpriteWidth()/2 - barWidth/2, floorf(entity.getY())};

    DrawRectangleV(barPos, {barWidth, barHeight}, DARKGRAY);

    DrawRectangleV(barPos, {barWidth * ratio, barHeight}, RED);

    if (isTargeted)
    {
        DrawRectangleLines(barPos.x - 1, barPos.y - 1, barWidth + 2, barHeight + 2, YELLOW);
    }
}
