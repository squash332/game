#pragma once

#include "Entity.hpp"
#include "Animation.hpp"

#define ABILITY_ICON_SIZE_VECTOR {32, 32}

struct Ability
{
    int id;
    Texture2D icon;
    Vector2 position;
    std::string name;
};

enum class PlayerClass
{
    Warrior,
    Mage,
    Paladin
};
class Player : public Entity
{
public:
    Player(std::string name);

    void update(float delta, int frame);
    void setDirection(Direction dir);
    void confirmMove(bool canX, bool canY);
    void addDirection(Direction dir);

    AnimationState getAnimState() const { return anim_state_; }
    bool isAttacking() const { return is_attacking_; }
    int getAttackStartFrame() const { return attack_start_frame_; }

    void attack(Direction dir);
    std::vector<Ability> loadAbilitiesForClass(PlayerClass playerClass);
    std::vector<Ability> getAbilities() const;
    int frame_number_ = 0;

private:
    std::string name_;
    AnimationState anim_state_;
    Direction last_direction_ = Direction::None;
    std::vector<Ability> abilities_;
    bool is_attacking_ = false;
    float attack_timer_ = 0.0f;
    int attack_start_frame_ = 0;
};
