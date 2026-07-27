#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"

class HUD {
    public:
    HUD();
    HUD(const HUD& other) = delete;
    ~HUD();

    void drawPlayerFrame(const Player& other);
    void drawTargetedFrame(const Entity& other);
    protected:
    private:
    Rectangle player_frame_;
    Rectangle targeted_frame_;
    Rectangle focus_frame_;

};
