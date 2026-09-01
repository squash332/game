#include "HUD.hpp"

HUD::HUD() : player_frame_({10.0f, 10.0f, 60.0f, 10.0f}),
             targeted_frame_({80.0f, 10.0f, 60.0f, 10.0f})
{
}

HUD::~HUD()
{
}

// Draws the player's frame, containing icon, stats, castbar
void HUD::drawPlayerFrame(const Player &player)
{
    DrawRectangleV({player_frame_.x, player_frame_.y}, {player_frame_.width, player_frame_.height}, DARKGRAY);
    DrawRectangleV({player_frame_.x, player_frame_.y}, {player_frame_.width, player_frame_.height}, GREEN);
}

// Draws the player's target frame (enemy/ally), containing icon, stats, castbar and it's targeted object
void HUD::drawTargetedFrame(const Entity &entity)
{
    float ratio = (float)entity.getCurrentHealth() / (float)entity.getMaxHealth();

    DrawRectangleV({targeted_frame_.x, targeted_frame_.y}, {targeted_frame_.width, targeted_frame_.height}, DARKGRAY);

    if (entity.is_ally_ == true)
    {
        DrawRectangleV({targeted_frame_.x, targeted_frame_.y}, {targeted_frame_.width * ratio, targeted_frame_.height}, GREEN);
    }
    else
    {
        DrawRectangleV({targeted_frame_.x, targeted_frame_.y}, {targeted_frame_.width * ratio, targeted_frame_.height}, RED);
    }
}

Rectangle HUD::getPlayerFrame() const
{
    return player_frame_;
}

Rectangle HUD::getTargetFrame() const
{
    return targeted_frame_;
}

Rectangle HUD::getFocusFrame() const
{
    return focus_frame_;
}
