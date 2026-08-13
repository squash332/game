#pragma once
#include "Entity.hpp"

class Enemy : public Entity
{
public:
    Enemy(std::string name);
    Enemy(const Enemy &other) = default;
    ~Enemy() = default;

    float getWidth() const { return width_; }
    float getHeight() const { return height_; }

protected:
private:
    std::string name_;
    float width_, height_;
};