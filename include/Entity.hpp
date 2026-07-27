#pragma once

#include "Common.hpp"
#include "Direction.hpp"
#include "raylib.h"
#include "Constants.hpp"

class Entity
{
public:
  Entity(float x, float y, bool isAlly);
  Entity(const Entity &other) = delete;
  virtual ~Entity() = default;

  void setPosition(float, float);
  float getX() const;
  float getY() const;
  float getNextX() const;
  float getNextY() const;
  float getCurrentHealth() const;
  float getMaxHealth() const;
  float getWidth() const;
  float getHeight() const;

  bool is_ally_;
protected:
  float max_health_;
  float current_health_;
  const char *name_;
  float x_, y_;
  float next_x_, next_y_;
  Direction direction_;
  float width_, height_;
};
