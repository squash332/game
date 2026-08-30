#include "Entity.hpp"

Entity::Entity(float x, float y, bool isAlly, float sprite_width, float sprite_height, float hitbox_width, float hitbox_height, MeleeRangeCircle melee_hitbox)
    : x_(x),
      y_(y),
      current_health_(100),
      max_health_(100),
      is_ally_(isAlly),
      sprite_width_(sprite_width),
      sprite_height_(sprite_height),
      hitbox_width_(hitbox_width),
      hitbox_height_(hitbox_height),
      melee_hitbox_{{sprite_width_ / 2, sprite_height_ / 2}, sprite_width_ / 2}
{
    direction_ = Direction::None;
    in_melee_range_ = false;
    std::cout << "entity constructor ran" << std::endl;
}

void Entity::setPosition(float x, float y)
{
    x_ = x;
    y_ = y;
}

float Entity::getX() const
{
    return x_;
}

float Entity::getY() const
{
    return y_;
}

float Entity::getNextX() const
{
    return next_x_;
}

float Entity::getNextY() const
{
    return next_y_;
}

float Entity::getCurrentHealth() const
{
    return current_health_;
}

float Entity::getMaxHealth() const
{
    return max_health_;
}

float Entity::getHitboxWidth() const
{
    return hitbox_width_;
}

float Entity::getHitboxHeight() const
{
    return hitbox_height_;
}

float Entity::getSpriteWidth() const
{
    return sprite_width_;
}

float Entity::getSpriteHeight() const
{
    return sprite_height_;
}

Rectangle Entity::getHitboxAt(float posX, float posY) const
{
    float offsetX = sprite_width_ / 2 - hitbox_width_ / 2;
    float offsetY = sprite_height_ - hitbox_height_ * 2;

    return Rectangle{posX + offsetX, posY + offsetY, hitbox_width_, hitbox_height_};
}

MeleeRangeCircle Entity::getMeleeHitbox() const
{
    MeleeRangeCircle circle = melee_hitbox_;
    circle.center.x += x_;
    circle.center.y += y_;

    return circle;
}

bool Entity::isInMeleeRange() const
{
    return in_melee_range_;
}

void Entity::setMeleeRange(bool melee_range)
{
    in_melee_range_ = melee_range;
}
