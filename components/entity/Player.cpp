#include "Player.hpp"
#include "Constants.hpp"
#include "Entity.hpp"
#include <math.h>

Player::Player(std::string name)
    : Entity(50.0f, 100.0f),
      name_(name),
      width_(static_cast<float>(CHARACTER_WIDTH)),
      height_(static_cast<float>(CHARACTER_HEIGHT))
{
    std::cout << "player constructor ran" << std::endl;
}

void Player::update(float delta, int frame)
{
    frame_number_ = frame;
    next_x_ = x_;
    next_y_ = y_;

    bool is_moving_vertical = (direction_ & Direction::Up) || (direction_ & Direction::Down);
    bool is_moving_horizontal = (direction_ & Direction::Right) || (direction_ & Direction::Left);

    // calculate diagonal step size
    float DIAGONAL_INDEX = MOVEMENT_INDEX / sqrt(2.0f);
    float step = ((is_moving_vertical && is_moving_horizontal) ? DIAGONAL_INDEX : MOVEMENT_INDEX) * delta;

    if (direction_ & Direction::Up)
        next_y_ -= step;
 
    if (direction_ & Direction::Down)
        next_y_ += step;

    if (direction_ & Direction::Right)
        next_x_ += step;

    if (direction_ & Direction::Left)
        next_x_ -= step;

    direction_ = Direction::None;
    DrawCircleV({floorf(getX() + getWidth() / 2), floorf(getY() + getHeight() - TILE_SIZE / 4)}, TILE_SIZE / 2, Fade(RED, 0.3f));
}


void Player::attack() {
    // ATTACK BASED ON TARGET
}

void Player::setDirection(Direction dir)
{
    direction_ = dir;
}

void Player::confirmMove()
{
    x_ = next_x_;
    y_ = next_y_;
}

void Player::addDirection(Direction dir)
{
    direction_ = direction_ | dir;
}
