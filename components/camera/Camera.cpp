#include "Camera.hpp"

Cam2d::Cam2d()
{
    camera_ = {0};
    // camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera_.offset = (Vector2){VIRTUAL_WIDTH / 2.0f, VIRTUAL_HEIGHT / 2.0f};
    camera_.rotation = {0.0f};
    camera_.zoom = {1.0f};
}

void Cam2d::beginFrame()
{
    BeginMode2D(camera_);
}

// Called with the player's position which the camera actively tracks.
void Cam2d::update(float player_x, float player_y, float delta)
{
    Vector2 desired = {floorf(player_x + TILE_SIZE / 2), floorf(player_y + TILE_SIZE / 2)};

    float lerpSpeed = 4.0f; // higher = snappier, lower = more lag/smoothing
    float t = 1.0f - expf(-lerpSpeed * delta);

    camera_.target.x = floorf(camera_.target.x + (desired.x - camera_.target.x) * t);
    camera_.target.y = floorf(camera_.target.y + (desired.y - camera_.target.y) * t);

    handleZoom();
}

void Cam2d::endFrame()
{
    EndMode2D();
}

// Handles zooming out and zooming in.
void Cam2d::handleZoom()
{
    if (camera_.zoom < 0.5f)
        camera_.zoom = 0.5f;

    camera_.zoom = expf(logf(camera_.zoom) + ((float)GetMouseWheelMove() * 0.1f));
}

void Cam2d::resetZoom()
{
    // TODO
}

// TODO
// make camera offset the target when approaching the map's end and not show parts which are not parts of map.
