#include "ActionBar.hpp"

ActionBar::ActionBar() : rows_(1), cols_(2), slotSize_(ABILITY_ICON_SIZE), iconPadding_(5)
{
    Settings settings = loadSettings(SETTINGS_PATH);
    if (settings.action_bar_config.width == 0 && settings.action_bar_config.height == 0)
    {
        float totalWidth = cols_ * slotSize_ + (cols_ + 1) * iconPadding_;
        float totalHeight = rows_ * slotSize_ + (rows_ + 1) * iconPadding_;
        action_bar_ = {
            (VIRTUAL_WIDTH - totalWidth) / 2.0f,
            VIRTUAL_HEIGHT - totalHeight,
            totalWidth,
            totalHeight};
    }
    else {
        action_bar_ = settings.action_bar_config;
    }
    std::cout << "action bar constructed" << std::endl;
}

void ActionBar::draw(const Player &player)
{
    // TODO: fix outline math for the actionbar

    const auto &abilities = player.getAbilities();

    for (size_t i = 0; i < abilities.size(); i++)
    {
        int row = i / cols_;
        int col = i % cols_;

        Vector2 slotPos = {
            action_bar_.x + iconPadding_ + col * (slotSize_ + iconPadding_),
            action_bar_.y + iconPadding_ + row * (slotSize_ + iconPadding_)};

        DrawTextureV(abilities[i].icon, slotPos, WHITE);
    }
}

void ActionBar::handleBarClick()
{
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return;
    if (drag_state_.active)
        return;

    if (CheckCollisionPointRec(mouse, action_bar_))
        drag_state_.start(&action_bar_, {action_bar_.x, action_bar_.y});
}

void ActionBar::handleDrag()
{
    if (!drag_state_.active)
        return;

    drag_state_.update();

    Rectangle *bar = static_cast<Rectangle *>(drag_state_.dragged_item);
    bar->x = drag_state_.current_pos.x;
    bar->y = drag_state_.current_pos.y;

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        drag_state_.end();
}

void ActionBar::update()
{
    handleBarClick();
    handleDrag();
}

Rectangle ActionBar::getActionBar() const
{

    return action_bar_;
}

void ActionBar::setActionBarPos(Rectangle pos)
{
    action_bar_.x = pos.x;
    action_bar_.y = pos.y;
}
