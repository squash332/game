#pragma once

#include "Common.hpp"
#include "Direction.hpp"
#include "raylib.h"

class Entity
{
public:
  Entity(float, float);
  Entity(const Entity &other) = delete;
  virtual ~Entity() = default;

  void setPosition(float, float);
  float getX() const;
  float getY() const;
  float getNextX() const;
  float getNextY() const;
  float getCurrentHealth() const;
  float getMaxHealth() const;

protected:
  float max_health_;
  float current_health_;
  const char *name_;
  float x_, y_;
  float next_x_, next_y_;
  Direction direction_;
};
