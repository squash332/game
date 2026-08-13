#pragma once

#include <iostream>

// WINDOW
constexpr int VIRTUAL_WIDTH = 480;
constexpr int VIRTUAL_HEIGHT = 270;
constexpr int TILE_SIZE = 16;

// ANIMATION
constexpr int NR_OF_FRAMES_IDLE = 2;
constexpr int NR_OF_FRAMES_MOVING = 9;
// constexpr int NR_OF_FRAMES_ATTACKING =

// MOVEMENT
#define MOVEMENT_INDEX 120

// CHARACTER SPRITE RELATED (drawing) RED
constexpr int SPRITE_WIDTH = 64;
constexpr int SPRITE_HEIGHT = 64;

constexpr float HITBOX_WIDTH_RATIO = 0.25f;  // hitbox is 1/4 sprite's width
constexpr float HITBOX_HEIGHT_RATIO = 0.25f;  // hitbox is 1/2 sprite's height

// COLLISION (movement hitbox — small, near the feet) GREEN
constexpr int HITBOX_WIDTH = (int)(SPRITE_WIDTH * HITBOX_WIDTH_RATIO); 
constexpr int HITBOX_HEIGHT = (int)(SPRITE_HEIGHT * HITBOX_HEIGHT_RATIO); 


// ENEMY sprite
constexpr int ENEMY_SPRITE_WIDTH = 16;
constexpr int ENEMY_SPRITE_HEIGHT = 32;