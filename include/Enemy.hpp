#pragma once
#include "Entity.hpp"

class Enemy : public Entity
{
public:
    Enemy(std::string name);
    Enemy(const Enemy &other) = default;
    ~Enemy() = default;

protected:
private:
    std::string name_;
};