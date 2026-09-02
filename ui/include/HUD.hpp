#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include "Settings.hpp"

class HUD {
    public:
    HUD();
    HUD(const HUD& other) = delete;
    ~HUD();

    void drawPlayerFrame(const Player& other);
    void drawTargetedFrame(const Entity& other);
    Rectangle getPlayerFrame() const;
    Rectangle getTargetFrame() const;
    Rectangle getFocusFrame() const;

    protected:
    private:
    Rectangle player_frame_;
    Rectangle targeted_frame_;
    Rectangle focus_frame_;

};
