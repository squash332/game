#include "Entity.hpp"

Entity::Entity(float x, float y): x_(x), y_(y), health_(100) {
    std::cout << "entity constructor ran" << std::endl;
}

void Entity::setPosition(float x, float y) {
    x_ = x;
    y_ = y;
}

float Entity::getX() const {
    return x_;
}

float Entity::getY() const {
    return y_;
}

float Entity::getNextX() const {
    return next_x_;
}

float Entity::getNextY() const {
    return next_y_;
}