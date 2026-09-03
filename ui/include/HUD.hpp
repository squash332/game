#pragma once

#include "raylib.h"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Constants.hpp"
#include "Settings.hpp"
#include "DragDropManager.hpp"
#include "Mouse.hpp"

struct Button
{
    Rectangle bounds;
    std::string label;

    void setBounds(Vector2 newPos) {
        bounds.x = newPos.x;
        bounds.y = newPos.y;
    }
};

class HUD
{
public:
    HUD();
    HUD(const HUD &other) = delete;
    ~HUD();

    void drawPlayerFrame(const Player &other);
    void drawTargetedFrame(const Entity &other);
    // void drawFocusFrame(const Entity &other);
    void drawSettingsWindow();
    void drawCenteredText(const std::string &text, Rectangle bounds, int fontSize, Color color);
    void drawButton(const Button &button, int fontSize, Color bgColor, Color textColor);


    void update();
    
    void setPlayerFrame(Rectangle frame);
    void setTargetFrame(Rectangle frame);
    // void setFocusFrame(Rectangle newPos);
    
    Rectangle getPlayerFrame() const;
    Rectangle getTargetFrame() const;
    Rectangle getFocusFrame() const;
    Rectangle getBtnEditModeBounds() const;

protected:
private:
    Rectangle player_frame_;
    Rectangle targeted_frame_;
    Rectangle focus_frame_;
    DragState drag_state_;
    Rectangle settings_window_;
    Button edit_mode_button_;
    void handleComponentClick();
    void handleDrag();
};
