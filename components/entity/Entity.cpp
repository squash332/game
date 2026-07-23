#include "Entity.hpp"

Entity::Entity(float x, float y)
    : x_(x),
      y_(y),
      current_health_(100),
      max_health_(100)
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
