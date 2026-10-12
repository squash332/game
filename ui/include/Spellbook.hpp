#pragma once

#include <vector>
#include <Ability.hpp>

#include "raylib.h"

enum class PlayerClass
{
    Warrior,
    Mage,
    Paladin
};

class Spellbook
{
public:
    Spellbook();
    Spellbook(const Spellbook &other) = delete;
    ~Spellbook() = default;

    void addAbility(const Ability &ability);
    void loadForClass(PlayerClass playerClass);
    void draw();

    Ability *getAbility(int id);
    const Ability *getAbility(int id) const;

    std::vector<Ability> &getAbilities();
    const std::vector<Ability> &getAbilities() const;

private:
    std::vector<Ability> abilities_;
    Rectangle spellbook_box_;
};