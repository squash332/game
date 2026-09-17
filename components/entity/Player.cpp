#include "Player.hpp"
#include "Constants.hpp"
#include <math.h>

Player::Player(std::string name)
    : Entity(50.0f, 150.0f, true, SPRITE_WIDTH, SPRITE_HEIGHT, HITBOX_WIDTH, HITBOX_HEIGHT, MeleeRangeCircle{}),
      name_(name),
      anim_state_(AnimationState::IdleDown)
{
    std::cout << "player constructor ran" << std::endl;
    std::cout << "player width: " << hitbox_width_ << std::endl;
    std::cout << "player height: " << hitbox_height_ << std::endl;
    abilities_ = loadAbilitiesForClass(PlayerClass::Warrior);
    in_melee_range_ = false;
}

void Player::update(float delta, int frame)
{
    frame_number_ = frame;
    if (is_attacking_)
    {
        attack_timer_ += delta;
        float attackDuration = NR_OF_FRAMES_ATTACKING * 0.1f;
        if (attack_timer_ >= attackDuration)
        {
            is_attacking_ = false;
        }
    }
    // need to adjust which frame to draw based on state: idle or moving or attacking
    next_x_ = x_;
    next_y_ = y_;

    // ability cooldown timer
    for (auto &ability : abilities_) {
        if (ability.cooldown_remaining > 0.0f)
            ability.cooldown_remaining -= delta;

        if (ability.cooldown_remaining == 0.0f || ability.cooldown_remaining < 0.0f) 
            ability.cooldown_remaining = 0.0f;

    }

    bool is_moving_vertical = (direction_ & Direction::Up) || (direction_ & Direction::Down);
    bool is_moving_horizontal = (direction_ & Direction::Right) || (direction_ & Direction::Left);

    // calculate diagonal step size
    float DIAGONAL_INDEX = MOVEMENT_INDEX / sqrt(2.0f);
    float step = ((is_moving_vertical && is_moving_horizontal) ? DIAGONAL_INDEX : MOVEMENT_INDEX) * delta;

    bool moved = false;

    if (direction_ & Direction::Up)
    {
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkUp;

        if (IsKeyDown(KEY_W))
            next_y_ -= step;

        last_direction_ = Direction::Up;
        moved = true;
    }

    if (direction_ & Direction::Down)
    {
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkDown;

        if (IsKeyDown(KEY_S))
            next_y_ += step;

        last_direction_ = Direction::Down;
        moved = true;
    }

    if (direction_ & Direction::Right)
    {
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkRight;

        if (IsKeyDown(KEY_D))
            next_x_ += step;

        last_direction_ = Direction::Right;
        moved = true;
    }

    if (direction_ & Direction::Left)
    {
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkLeft;

        if (IsKeyDown(KEY_A))
            next_x_ -= step;

        last_direction_ = Direction::Left;
        moved = true;
    }

    if (!moved && !is_attacking_)
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

void Player::attack(Direction dir, AbilityAnim animType)
{
    if (is_attacking_)
        return;
    is_attacking_ = true;
    attack_timer_ = 0.0f;
    attack_start_frame_ = frame_number_;
    direction_ = dir;
    anim_state_ = getAttackAnimState(dir, animType);
}

void Player::startCooldown(int abilityId)
{
    for (auto &ability : abilities_) {
        if (ability.id == abilityId) {
            ability.cooldown_remaining = ability.cooldown;
            return;
        }
    }
}

AnimationState Player::getAttackAnimState(Direction dir, AbilityAnim animType)
{
    switch (animType)
    {
    case AbilityAnim::Slash:
        switch (dir)
        {
        case Direction::Up:
            return AnimationState::SlashUp;
        case Direction::Down:
            return AnimationState::SlashDown;
        case Direction::Left:
            return AnimationState::SlashLeft;
        default:
            return AnimationState::SlashRight;
        }
    case AbilityAnim::Clap:
        switch (dir)
        {
        case Direction::Up:
            return AnimationState::ClapUp;
        case Direction::Down:
            return AnimationState::ClapDown;
        case Direction::Left:
            return AnimationState::ClapLeft;
        default:
            return AnimationState::ClapRight;
        }
    }
    return AnimationState::SlashRight;
}

std::vector<Ability> Player::loadAbilitiesForClass(PlayerClass playerClass)
{
    switch (playerClass)
    {
    case PlayerClass::Warrior:
        return {
            Ability{
                .id = 1,
                .name = "Slash",
                .icon = LoadTexture("res/slash.png"),
                .description = "A quick melee attack that deals damage.",
                .damage = 20,
                .cooldown = 3.0f,
                .animType = AbilityAnim::Slash

            },
            Ability{
                .id = 2,
                .name = "Clap",
                .icon = LoadTexture("res/clap.png"),
                .description = "An AoE attack that deals damage to multiple enemies.",
                .damage = 10,
                .cooldown = 5.0f,
                .animType = AbilityAnim::Clap}};
    }
    return {};
}

const std::vector<Ability> &Player::getAbilities() const
{
    return abilities_;
}

void Player::swapAbilities(int indexA, int indexB)
{
    if (indexA >= 0 && indexB >= 0 && indexA < (int)abilities_.size() && indexB < (int)abilities_.size())
        std::swap(abilities_[indexA], abilities_[indexB]);
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
