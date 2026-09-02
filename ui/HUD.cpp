#include "HUD.hpp"

HUD::HUD()
{
    Settings settings = loadSettings(SETTINGS_PATH);
    player_frame_ = settings.player_frame_config;
    targeted_frame_ = settings.targeted_frame_config;
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

void HUD::drawSettingsWindow()
{
    Rectangle window;
    window.height = VIRTUAL_HEIGHT / 2;
    window.width = VIRTUAL_HEIGHT / 2;
    window.x = VIRTUAL_WIDTH / 2 - window.width / 2;
    window.y = VIRTUAL_HEIGHT / 2 - window.height / 2;

    // draw window
    DrawRectangle(window.x, window.y, window.width, window.height, Fade(GRAY, 0.7));

    // buttons on top of window
    Button edit_mode = {{window.x + BTN_PADDING, window.y + BTN_PADDING, window.width - BTN_PADDING * 2, window.height / NR_OF_OPTIONS}, "Edit mode"};
    drawButton(edit_mode, FONT_SIZE, BUTTON_BG_COLOR, WHITE);
}

void HUD::drawCenteredText(const std::string &text, Rectangle bounds, int fontSize, Color color)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - fontSize) / 2.0f;

    DrawText(text.c_str(), (int)textX, (int)textY, fontSize, color);
}

bool HUD::drawButton(const Button &button, int fontSize, Color bgColor, Color textColor)
{
    DrawRectangleRec(button.bounds, bgColor);
    drawCenteredText(button.label, button.bounds, fontSize, textColor);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), button.bounds))
    {
        return true;
    }
    return false;
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
