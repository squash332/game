#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    Player(std::string name);

    void update(float delta, int frame);
    void setDirection(Direction dir);
    void confirmMove();
    void addDirection(Direction dir);

    int frame_number_ = 0;
private:
    std::string name_;
};
