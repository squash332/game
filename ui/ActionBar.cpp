#include "ActionBar.hpp"

ActionBar::ActionBar() : rows_(1), cols_(3), slotSize_(ABILITY_ICON_SIZE), iconPadding_(5)
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
    else
    {
        action_bar_ = settings.action_bar_config;
    }

    slot_keybinds_ = {{KEY_ONE}, {KEY_TWO}, {KEY_THREE}};
    std::cout << "action bar constructed" << std::endl;
}

void ActionBar::draw(const Player &player)
{

    const auto &abilities = player.getAbilities();
    int slotCount = rows_ * cols_;

    DrawRectangleRec(action_bar_, COLOR_WINDOW_BG);

    for (int i = 0; i < slotCount; i++)
    {
        Rectangle slot = getSlotBounds(i);

        // draw the ability icon if this slot has one
        if (i < (int)slot_keybinds_.size())
        {
            DrawTextureV(abilities[i].icon, {floorf(slot.x), floorf(slot.y)}, WHITE);
        }
        // draw the slot's keybind label — always, occupied or not
        std::string keyLabel = keybindToString(slot_keybinds_[i]);
        DrawText(keyLabel.c_str(), slot.x + 2, slot.y + 2, 8, WHITE);
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

int ActionBar::getHoveredSlot(size_t abilityCount) const
{
    for (size_t i = 0; i < abilityCount; i++)
    {
        if (CheckCollisionPointRec(mouse, getSlotBounds(i)))
            return (int)i;
    }
    return -1;
}

int ActionBar::getActionBarCols() const
{
    return cols_;
}

Rectangle ActionBar::getSlotBounds(int i) const
{
    int row = i / cols_;
    int col = i % cols_;

    return {
        action_bar_.x + iconPadding_ + col * (slotSize_ + iconPadding_),
        action_bar_.y + iconPadding_ + row * (slotSize_ + iconPadding_),
        slotSize_,
        slotSize_};
}

int ActionBar::getActionBarRows() const
{
    return rows_;
}
