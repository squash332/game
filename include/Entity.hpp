#pragma once

#include "Common.hpp"
#include "Direction.hpp"
#include "raylib.h"
#include "Constants.hpp"

struct MeleeRangeCircle
{
  Vector2 center;
  float radius;
};

class Entity
{
public:
  Entity(float x, float y, bool isAlly, float sprite_width, float sprite_height, float hitbox_width, float hitbox_height, MeleeRangeCircle melee);
  Entity(const Entity &other) = default;
  virtual ~Entity() = default;

  void setPosition(float, float);
  float getX() const;
  float getY() const;
  float getNextX() const;
  float getNextY() const;
  float getCurrentHealth() const;
  float getMaxHealth() const;
  float getHitboxWidth() const;
  float getHitboxHeight() const;
  float getSpriteWidth() const;
  float getSpriteHeight() const;
  Rectangle getHitboxAt(float posX, float posY) const;
  MeleeRangeCircle getMeleeHitbox() const;
  bool isInMeleeRange() const;
  void setMeleeRange(bool melee_range);
  void takeDamage(float damage);

  bool is_ally_;

protected:
  float max_health_;
  float current_health_;
  const char *name_;
  float x_, y_;
  float next_x_, next_y_;
  Direction direction_;

  float sprite_width_;
  float sprite_height_;
  float hitbox_width_;
  float hitbox_height_;
  MeleeRangeCircle melee_hitbox_;
  bool in_melee_range_;
};
