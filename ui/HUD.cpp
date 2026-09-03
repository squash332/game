#include "HUD.hpp"

HUD::HUD()
{
    Settings settings = loadSettings(SETTINGS_PATH);
    player_frame_ = settings.player_frame_config;
    targeted_frame_ = settings.targeted_frame_config;
    settings_window_.height = VIRTUAL_HEIGHT / 2;
    settings_window_.width = VIRTUAL_HEIGHT / 2;
    settings_window_.x = VIRTUAL_WIDTH / 2 - settings_window_.width / 2;
    settings_window_.y = VIRTUAL_HEIGHT / 2 - settings_window_.height / 2;
    edit_mode_button_ = {{settings_window_.x + BTN_PADDING, settings_window_.y + BTN_PADDING, settings_window_.width - BTN_PADDING * 2, settings_window_.height / NR_OF_OPTIONS}, "Edit mode"};
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

void HUD::drawSettingsWindow( )
{
    // draw window
    DrawRectangleRec(settings_window_, Fade(GRAY, 0.7));

    // buttons on top of window
    drawButton(edit_mode_button_, FONT_SIZE, COLOR_BUTTON_BG, WHITE);
}

void HUD::drawCenteredText(const std::string &text, Rectangle bounds, int fontSize, Color color)
{
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = bounds.x + (bounds.width - textWidth) / 2.0f;
    float textY = bounds.y + (bounds.height - fontSize) / 2.0f;

    DrawText(text.c_str(), (int)textX, (int)textY, fontSize, color);
}

void HUD::drawButton(const Button &button, int fontSize, Color bgColor, Color textColor)
{
    DrawRectangleRec(button.bounds, bgColor);
    drawCenteredText(button.label, button.bounds, fontSize, textColor);

}

// detects a mouse click and signals that drag'n drop action can begin
void HUD::handleComponentClick(Vector2 mouse)
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return;
    if (drag_state_.active)
        return;

    if (CheckCollisionPointRec(mouse, player_frame_))
    {
        drag_state_.start(&player_frame_, mouse, {player_frame_.x, player_frame_.y});
    }
    else if (CheckCollisionPointRec(mouse, targeted_frame_))
    {
        drag_state_.start(&targeted_frame_, mouse, {targeted_frame_.x, targeted_frame_.y});
    }
}

void HUD::handleDrag(Vector2 mouse)
{
    if (!drag_state_.active)
        return;

    drag_state_.update(mouse);

    Rectangle *frame = static_cast<Rectangle *>(drag_state_.dragged_item);
    frame->x = drag_state_.current_pos.x;
    frame->y = drag_state_.current_pos.y;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        drag_state_.end();
    }
}

void HUD::update(Vector2 mouse)
{
    handleComponentClick(mouse);
    handleDrag(mouse);
}

void HUD::setPlayerFrame(Rectangle frame)
{  
   player_frame_ = frame; 
}

void HUD::setTargetFrame(Rectangle frame)
{
    targeted_frame_ = frame;
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

Rectangle HUD::getBtnEditModeBounds() const
{
    return edit_mode_button_.bounds;
}
