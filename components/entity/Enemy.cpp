#include "Enemy.hpp"
#include "Constants.hpp"
#include "Entity.hpp"

Enemy::Enemy(std::string name) : Entity(70.0f, 100.0f, false),
                                 name_("")
{
    std::cout << "enemy constructor ran" << std::endl;
}