#include "Entity.hpp"

Entity::Entity(float x, float y, bool isAlly, float sprite_width, float sprite_height, float hitbox_width, float hitbox_height)
    : x_(x),
      y_(y),
      current_health_(100),
      max_health_(100),
      is_ally_(isAlly),
      sprite_width_(sprite_width),
      sprite_height_(sprite_height),
      hitbox_width_(hitbox_width),
      hitbox_height_(hitbox_height)
{
    direction_ = Direction::None;
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
    float offsetY = sprite_height_ - hitbox_height_;

    return Rectangle{posX + offsetX, posY + offsetY, hitbox_width_, hitbox_height_};
}
