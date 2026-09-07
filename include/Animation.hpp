#pragma once
#include "Constants.hpp"

struct AnimationData
{
    int row;
    int frameCount;
    float frameWidth = SPRITE_WIDTH;
    float frameHeight = SPRITE_HEIGHT;
};

enum class AnimationState
{
    IdleUp,
    IdleDown,
    IdleLeft,
    IdleRight,

    WalkUp,
    WalkDown,
    WalkLeft,
    WalkRight,

    SlashUp,
    SlashLeft,
    SlashRight,
    SlashDown

};

inline AnimationData getAnimData(AnimationState state)
{
    switch (state)
    {
    case AnimationState::IdleDown:
        return {0, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleLeft:
        return {1, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleRight:
        return {2, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleUp:
        return {3, NR_OF_FRAMES_IDLE};
    case AnimationState::WalkDown:
        return {4, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkLeft:
        return {5, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkRight:
        return {6, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkUp:
        return {7, NR_OF_FRAMES_MOVING};
    case AnimationState::SlashDown:
        return {8, NR_OF_FRAMES_ATTACKING};
    case AnimationState::SlashLeft:
        return {9, NR_OF_FRAMES_ATTACKING};
    case AnimationState::SlashRight:
        return {10, NR_OF_FRAMES_ATTACKING};
    case AnimationState::SlashUp:
        return {11, NR_OF_FRAMES_ATTACKING};
    }

    return {0, 1};
}