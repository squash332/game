#include "Player.hpp"
#include "Constants.hpp"
#include "Entity.hpp"

Player::Player(std::string name)
    : Entity(0.0f, 32.0f),
    name_(name)
{
  std::cout << "player constructor ran" << std::endl;
}

void Player::update() {

    next_x_ = x_;
    next_y_ = y_;
    
    
    switch(direction_) {
        case Direction::Up:
            next_y_ -= TILE_SIZE;
            break;
        
        case Direction::Down:
            next_y_ += TILE_SIZE;
            break;
        
        case Direction::Right:
           next_x_ += TILE_SIZE;
            break;
        
        case Direction::Left:
           next_x_ -= TILE_SIZE;
            break;

        default:
            break;
    }
    direction_ = Direction::None; // after moving, set direction to none so he stops moving
}

void Player::setDirection(Direction dir) {
    direction_ = dir;
}

void Player::confirmMove() {
    x_ = next_x_;
    y_ = next_y_;
}

