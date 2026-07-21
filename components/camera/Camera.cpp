#include "Camera.hpp"

Cam2d::Cam2d(){
    camera_ = {0};
    // camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera_.offset = (Vector2){ VIRTUAL_WIDTH/2.0f, VIRTUAL_HEIGHT/2.0f };
    camera_.rotation = {0.0f};
    camera_.zoom = {1.0f};

    
}

void Cam2d::beginFrame() {
    BeginMode2D(camera_);
}

// Called with the player's position which the camera actively tracks.
void Cam2d::update(float player_x, float player_y) {
    camera_.target = { player_x + TILE_SIZE /2, player_y + TILE_SIZE /2};
    // DrawLine((int)camera_.target.x, -VIRTUAL_HEIGHT*10, (int)camera_.target.x, VIRTUAL_HEIGHT*10, GREEN);
    // DrawLine(-VIRTUAL_WIDTH*10, (int)camera_.target.y, VIRTUAL_WIDTH*10, (int)camera_.target.y, GREEN);
    handleZoom();
}

void Cam2d::endFrame() {
    EndMode2D();
}

// Handles zooming out and zooming in.
void Cam2d::handleZoom() {
    if (camera_.zoom > 2.0f) camera_.zoom = 2.0f;
    if (camera_.zoom < 0.5f) camera_.zoom = 0.5f;

    camera_.zoom = expf(logf(camera_.zoom) + ((float)GetMouseWheelMove()*0.1f));
}

void Cam2d::resetZoom() {
    // TODO 
}

// TODO 
// make camera offset the target when approaching the map's end and not show parts which are not parts of map.

