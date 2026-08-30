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

    bool is_moving_vertical = (direction_ & Direction::Up) || (direction_ & Direction::Down);
    bool is_moving_horizontal = (direction_ & Direction::Right) || (direction_ & Direction::Left);

    // calculate diagonal step size
    float DIAGONAL_INDEX = MOVEMENT_INDEX / sqrt(2.0f);
    float step = ((is_moving_vertical && is_moving_horizontal) ? DIAGONAL_INDEX : MOVEMENT_INDEX) * delta;

    bool moved = false;

    if (direction_ & Direction::Up)
    {
        next_y_ -= step;
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkUp;
        last_direction_ = Direction::Up;
        moved = true;
    }

    if (direction_ & Direction::Down)
    {
        next_y_ += step;
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkDown;
        last_direction_ = Direction::Down;
        moved = true;
    }

    if (direction_ & Direction::Right)
    {
        next_x_ += step;
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkRight;
        last_direction_ = Direction::Right;
        moved = true;
    }

    if (direction_ & Direction::Left)
    {
        next_x_ -= step;
        if (!is_attacking_)
            anim_state_ = AnimationState::WalkLeft;
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

void Player::attack()
{
    if (is_attacking_)
        return;
    is_attacking_ = true;
    attack_timer_ = 0.0f;
    attack_start_frame_ = frame_number_;

    switch (last_direction_)
    {
    case Direction::Up:
        anim_state_ = AnimationState::SlashUp;
        break;
    case Direction::Down:
        anim_state_ = AnimationState::SlashDown;
        break;
    case Direction::Left:
        anim_state_ = AnimationState::SlashLeft;
        break;
    case Direction::Right:
        anim_state_ = AnimationState::SlashRight;
        break;
    default:
        anim_state_ = AnimationState::SlashRight;
        break;
    }
}

std::vector<Ability> Player::loadAbilitiesForClass(PlayerClass playerClass)
{
    switch (playerClass)
    {
    case PlayerClass::Warrior:
        return {{1, LoadTexture("res/slash.png"), ABILITY_ICON_SIZE_VECTOR, "Slash"}, {2, LoadTexture("res/clap.png"), ABILITY_ICON_SIZE_VECTOR, "Clap"}};
    }
    return {};
}

std::vector<Ability> Player::getAbilities() const
{
    return abilities_;
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
