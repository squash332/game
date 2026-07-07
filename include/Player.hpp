#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(std::string name);

    void update() override;
    void setDirection(Direction dir);
    void confirmMove();
    void addDirection(Direction dir);

private:
    std::string name_;
};
