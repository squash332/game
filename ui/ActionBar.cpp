#include "ActionBar.hpp"

ActionBar::ActionBar() : rows_(1), cols_(2), slotSize_(ABILITY_ICON_SIZE), iconPadding_(5)
{
    float totalWidth = cols_ * (slotSize_ + iconPadding_) - iconPadding_ ;
    float totalHeight = rows_ * (slotSize_ + iconPadding_);

    bounds_ = {
        (VIRTUAL_WIDTH - totalWidth) / 2.0f ,
        VIRTUAL_HEIGHT - totalHeight ,
        totalWidth,
        totalHeight
    };
    std::cout << "action bar constructed" << std::endl;
    std::cout << "position: " << bounds_.x << "," << bounds_.y << std::endl;
}

void ActionBar::draw(const Player &player)
{
    // DrawRectangleRec(bounds_, Fade(BLACK, 0.5));
    // TODO: fix outline math for the actionbar

    const auto &abilities = player.getAbilities();

    for (size_t i = 0; i < abilities.size(); i++)
    {
        int row = i / cols_;
        int col = i % cols_;

        Vector2 slotPos = {
            bounds_.x +  iconPadding_ + col * (slotSize_ + iconPadding_/2),
            bounds_.y + iconPadding_ + row * (slotSize_ + iconPadding_/2)};

        DrawTextureV(abilities[i].icon, slotPos, WHITE);
    }
}

void ActionBar::handleDrag()
{
}

void ActionBar::handleClick()
{
}

Rectangle ActionBar::getBounds() const
{

    return bounds_;
}