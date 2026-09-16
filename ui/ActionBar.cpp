#include "ActionBar.hpp"

ActionBar::ActionBar() : rows_(1), cols_(3), iconPadding_(5), grabbed_slot_(-1), slots_(rows_ * cols_)
{
    slots_[0].keybind.key = KEY_ONE;
    slots_[1].keybind.key = KEY_TWO;
    slots_[2].keybind.key = KEY_THREE;

    Settings settings = loadSettings(SETTINGS_PATH);

    if (settings.action_bar_config.width == 0 && settings.action_bar_config.height == 0)
    {
        buildDefaultActionBar();
    }
    else
    {
        action_bar_ = settings.action_bar_config;
    }

    std::cout << "action bar constructed" << std::endl;
}

void ActionBar::buildDefaultActionBar()
{
    const float slotSize = slots_[0].size;
    float totalWidth = cols_ * slotSize + (cols_ + 1) * iconPadding_;
    float totalHeight = rows_ * slotSize + (rows_ + 1) * iconPadding_;

    action_bar_ = {
        (VIRTUAL_WIDTH - totalWidth) / 2.0f,
        VIRTUAL_HEIGHT - totalHeight,
        totalWidth,
        totalHeight};
}

void ActionBar::draw(const Player &player)
{
    const auto &abilities = player.getAbilities();

    DrawRectangleRec(action_bar_, COLOR_WINDOW_BG);

    for (size_t i = 0; i < slots_.size(); ++i)
    {
        const auto &slot = slots_[i];
        const Rectangle bounds = getSlotBounds(i);

        if (i < abilities.size())
        {
            const auto &ability = abilities[i];

            DrawTextureV(ability.icon, {bounds.x, bounds.y}, WHITE);
            drawCooldown(bounds, ability, i);
        }

        drawKeybind(bounds, i);
    }

    if (grabbed_slot_ >= 0 && static_cast<size_t>(grabbed_slot_) < abilities.size())
    {
        DrawTextureV(abilities[grabbed_slot_].icon, mouse, WHITE);
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

/***
 * @brief Swaps abilities if player Shift clicks and holds LMB drags it to a valid position.
 * @returns Index of the slot in the action bar or -1 for returning
 */
int ActionBar::handleAbilitySwap(Player &player)
{
    const auto &abilities = player.getAbilities();

    // by having only this block in HOLDING_SHIFT, we can move the ability without holding shift the entire time
    // previously by having all the code in the if block, player would have a hanging icon to his cursor
    // if he decided to release shift and try to move an ability to a different slot
    if (HOLDING_SHIFT)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            grabbed_slot_ = getHoveredSlot(abilities.size());
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && grabbed_slot_ != -1)
    {
        int dropped = getHoveredSlot(abilities.size());
        if (dropped != -1 && dropped != grabbed_slot_)
            player.swapAbilities(grabbed_slot_, dropped);

        grabbed_slot_ = -1;
    }

    return -1;
}

void ActionBar::updateEditModeComponents()
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

Rectangle ActionBar::getSlotBounds(int i) const
{
    int row = i / cols_;
    int col = i % cols_;
    const float slotSize = slots_[0].size;

    return {
        action_bar_.x + iconPadding_ + col * (slotSize + iconPadding_),
        action_bar_.y + iconPadding_ + row * (slotSize + iconPadding_),
        slotSize,
        slotSize};
}

Keybind ActionBar::getSlotKeybind(int index) const
{
    if (index >= 0 && index < static_cast<int>(slots_.size()))
    {
        return slots_[index].keybind;
    }

    return {};
}

void ActionBar::drawCooldown(Rectangle bounds, const Ability &ability, int i)
{
    if (ability.cooldown_remaining <= 0.0f)
        return;

    const float fraction = ability.cooldown_remaining / ability.cooldown;

    const float overlayHeight = slots_[i].size * fraction;

    DrawRectangle(
        bounds.x,
        bounds.y + slots_[i].size - overlayHeight,
        slots_[i].size,
        overlayHeight,
        Fade(BLACK, 0.6f));

    const std::string text = std::to_string(static_cast<int>(std::ceil(ability.cooldown_remaining)));

    DrawText(
        text.c_str(),
        bounds.x + slots_[i].size / 2 - 4,
        bounds.y + slots_[i].size / 2 - 4,
        10,
        WHITE);
}

void ActionBar::drawKeybind(Rectangle bounds, int i)
{
    const std::string label = keybindToString(slots_[i].keybind);

    DrawText(
        label.c_str(),
        bounds.x + 2,
        bounds.y + 2,
        8,
        WHITE);
}
