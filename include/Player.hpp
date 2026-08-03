#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

class Player : public Entity
{
public:
    Player(std::string name);

    void update(float delta, int frame);
    void setDirection(Direction dir);
    void confirmMove();
    void addDirection(Direction dir);

    float getWidth() const { return width_; }
    float getHeight() const { return height_; }
    AnimationState getAnimState() const { return anim_state_; }

    void attack();

    int frame_number_ = 0;

private:
    std::string name_;
    float width_;
    float height_;
    AnimationState anim_state_;
    Direction last_direction_ = Direction::None;
};
