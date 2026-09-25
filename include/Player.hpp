#pragma once

#include "Entity.hpp"
#include "Animation.hpp"
#include "Ability.hpp"
#include "Spellbook.hpp"

class Player : public Entity
{
public:
    Player(std::string name, PlayerClass playerClass);

    void update(float delta, int frame);
    void setDirection(Direction dir);
    void confirmMove(bool canX, bool canY);
    void addDirection(Direction dir);

    AnimationState getAnimState() const { return anim_state_; }
    bool isAttacking() const { return is_attacking_; }
    int getAttackStartFrame() const { return attack_start_frame_; }

    void attack(Direction dir, AbilityAnim animType);
    AnimationState getAttackAnimState(Direction dir, AbilityAnim animType);
    Spellbook& getSpellbook();

    int frame_number_ = 0;
private:
    std::string name_;
    AnimationState anim_state_;
    Direction last_direction_ = Direction::None;
    Spellbook spellbook_;
    PlayerClass player_class_;
    bool is_attacking_ = false;
    float attack_timer_ = 0.0f;
    int attack_start_frame_ = 0;
};
