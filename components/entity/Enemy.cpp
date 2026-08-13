#include "Enemy.hpp"
#include "Constants.hpp"
#include "Entity.hpp"

Enemy::Enemy(std::string name) : Entity(70.0f, 100.0f, false, ENEMY_SPRITE_WIDTH, ENEMY_SPRITE_HEIGHT, HITBOX_WIDTH, HITBOX_WIDTH),
                                 name_(name)
                                 
{
    std::cout << "enemy constructor ran" << std::endl;
    std::cout << "enemy width: " << hitbox_width_ << std::endl;
    std::cout << "enemy height: " << hitbox_height_ << std::endl;
}

