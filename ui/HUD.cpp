#include "HUD.hpp"

HUD::HUD() : 
player_frame_({10.0f, 10.0f, 60.0f, 10.0f}),
targeted_frame_({80.0f, 10.0f, 60.0f, 10.0f})
{
}

HUD::~HUD()
{
}

// Draws the player's frame, containing icon, stats, castbar
void HUD::drawPlayerFrame(const Player &player)
{
    DrawRectangleRec(player_frame_, GREEN);
}

// Draws the player's target frame (enemy/ally), containing icon, stats, castbar and it's targeted object
void HUD::drawTargetedFrame(const Entity &other)
{
    if(other.is_ally_ == true) {
        DrawRectangleRec(targeted_frame_, GREEN);
    }
    else {
        DrawRectangleRec(targeted_frame_, RED);
    }
}