#include "Enemy.hpp"
#include "Constants.hpp"
#include "Entity.hpp"

Enemy::Enemy(std::string name) : Entity(70.0f, 100.0f, false),
                                 name_(""),
                                 width_(16.0f),
                                 height_(32.0f)
{
    std::cout << "enemy constructor ran" << std::endl;
    std::cout << "enemy width: " << width_ << std::endl;
    std::cout << "enemy height: " << height_ << std::endl;
}

