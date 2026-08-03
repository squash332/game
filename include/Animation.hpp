#pragma once
#include "Constants.hpp"

struct AnimationData
{
    int row;
    int frameCount;
};

enum class AnimationState {
    IdleUp,
    IdleDown,
    IdleLeft,
    IdleRight,

    WalkUp,
    WalkDown,
    WalkLeft,
    WalkRight
};

inline AnimationData getAnimData(AnimationState state)
{
    switch (state)
    {
    case AnimationState::IdleUp:
        return {0, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleLeft:
        return {1, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleDown:
        return {2, NR_OF_FRAMES_IDLE};
    case AnimationState::IdleRight:
        return {3, NR_OF_FRAMES_IDLE};
    case AnimationState::WalkUp:
        return {8, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkLeft:
        return {9, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkDown:
        return {10, NR_OF_FRAMES_MOVING};
    case AnimationState::WalkRight:
        return {11, NR_OF_FRAMES_MOVING};
    }
    
    return { 0, 1 };
}