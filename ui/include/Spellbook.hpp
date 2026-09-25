#pragma once

#include <vector>
#include <Ability.hpp>

enum class PlayerClass
{
    Warrior,
    Mage,
    Paladin
};

class Spellbook
{

public:
    void addAbility(const Ability &ability);
    void loadForClass(PlayerClass playerClass);

    Ability *getAbility(int id);
    const Ability *getAbility(int id) const;

    std::vector<Ability> &getAbilities();
    const std::vector<Ability> &getAbilities() const;

private:
    std::vector<Ability> abilities_;
};