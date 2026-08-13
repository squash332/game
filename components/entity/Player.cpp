#include "Player.hpp"
#include "Constants.hpp"
#include <math.h>

Player::Player(std::string name)
    : Entity(50.0f, 150.0f, true),
      name_(name),
      width_(static_cast<float>(HITBOX_WIDTH)),
      height_(static_cast<float>(HITBOX_HEIGHT)),
      anim_state_(AnimationState::IdleDown)
{
    std::cout << "player constructor ran" << std::endl;
}

void Player::update(float delta, int frame)
{
    // need to adjust which frame to draw based on state: idle or moving or attacking
    frame_number_ = frame;
    next_x_ = x_;
    next_y_ = y_;

    bool is_moving_vertical = (direction_ & Direction::Up) || (direction_ & Direction::Down);
    bool is_moving_horizontal = (direction_ & Direction::Right) || (direction_ & Direction::Left);

    // calculate diagonal step size
    float DIAGONAL_INDEX = MOVEMENT_INDEX / sqrt(2.0f);
    float step = ((is_moving_vertical && is_moving_horizontal) ? DIAGONAL_INDEX : MOVEMENT_INDEX) * delta;

    bool moved = false;

    if (direction_ & Direction::Up)
    {
        next_y_ -= step;
        anim_state_ = AnimationState::WalkUp;
        last_direction_ = Direction::Up;
        moved = true;
    }

    if (direction_ & Direction::Down)
    {
        next_y_ += step;
        anim_state_ = AnimationState::WalkDown;
        last_direction_ = Direction::Down;
        moved = true;
    }

    if (direction_ & Direction::Right)
    {
        next_x_ += step;
        anim_state_ = AnimationState::WalkRight;
        last_direction_ = Direction::Right;
        moved = true;
    }

    if (direction_ & Direction::Left)
    {
        next_x_ -= step;
        anim_state_ = AnimationState::WalkLeft;
        last_direction_ = Direction::Left;
        moved = true;
    }

    if (!moved)
    {
        switch (last_direction_)
        {
        case Direction::Up:
            anim_state_ = AnimationState::IdleUp;
            break;
        case Direction::Down:
            anim_state_ = AnimationState::IdleDown;
            break;
        case Direction::Left:
            anim_state_ = AnimationState::IdleLeft;
            break;
        case Direction::Right:
            anim_state_ = AnimationState::IdleRight;
            break;
        default:
            anim_state_ = AnimationState::IdleDown;
            break;
        }
    }

    direction_ = Direction::None;
}

Rectangle Player::getHitboxAt(float posX, float posY) const
{
    float offsetX = SPRITE_WIDTH / 2 - HITBOX_WIDTH / 2;
    float offsetY = SPRITE_HEIGHT - HITBOX_HEIGHT;
    return Rectangle{posX + offsetX, posY + offsetY, width_, height_};
}

void Player::attack()
{
    // ATTACK BASED ON TARGET
}

void Player::setDirection(Direction dir)
{
    direction_ = dir;
}

void Player::confirmMove(bool allowedX, bool allowedY)
{
    if (allowedX)
        x_ = next_x_;
    if (allowedY)
        y_ = next_y_;
}

void Player::addDirection(Direction dir)
{
    direction_ = direction_ | dir;
}
