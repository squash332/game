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
    float getRemainingGCD() const;
    float getDurationGCD() const;
    Direction getCurrentDirection() const;
    void startGCD();

    void attack(Direction dir, AbilityAnim animType);
    AnimationState getAttackAnimState(Direction dir, AbilityAnim animType);
    Spellbook& getSpellbook();

    int frame_number_;
private:
    std::string name_;
    AnimationState anim_state_;
    Direction last_direction_;
    Spellbook spellbook_;
    PlayerClass player_class_;
    bool is_attacking_;
    float attack_timer_;
    float global_cooldown_duration_;
    float global_cooldown_remaining_;
    int attack_start_frame_;
};
