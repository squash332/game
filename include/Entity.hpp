#pragma once

#include "Common.hpp"

enum class Direction
{
  Up,
  Down,
  Left,
  Right,
  None
};

class Entity
{
public:
  Entity(float, float);
  Entity(const Entity& other) = delete;
  virtual ~Entity() = default;
  
  virtual void update() = 0;

  void setPosition(float, float);
  float getX() const;
  float getY() const;
  float getNextX() const;
  float getNextY() const;

protected:
  uint16_t health_;
  const char* name_;
  float x_, y_;
  float next_x_, next_y_;
  Direction direction_ = Direction::None;
};
