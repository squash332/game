#include "Spellbook.hpp"

void Spellbook::addAbility(const Ability &ability)
{
    abilities_.push_back(ability);
}

void Spellbook::loadForClass(PlayerClass playerClass)
{
    abilities_.clear();

    switch (playerClass)
    {
    case PlayerClass::Warrior:
        abilities_ = {
            Ability{
                .id = 0,
                .name = "Slash",
                .icon = LoadTexture("res/slash.png"),
                .description = "A quick melee attack that deals damage.",
                .damage = 20,
                .cooldown = 3.0f,
                .animType = AbilityAnim::Slash
            },

            Ability{
                .id = 1,
                .name = "Clap",
                .icon = LoadTexture("res/clap.png"),
                .description = "An AoE attack that deals damage to multiple enemies.",
                .damage = 10,
                .cooldown = 5.0f,
                .animType = AbilityAnim::Clap
            }
        };
        break;

    case PlayerClass::Mage:
        // todo
        break;

    case PlayerClass::Paladin:
        // todo
        break;
    }
}


Ability *Spellbook::getAbility(int id)
{
    for (auto &ability : abilities_)
    {
        if (ability.id == id)
            return &ability;
    }

    return nullptr;
}

const Ability *Spellbook::getAbility(int id) const
{
    for (const auto &ability : abilities_)
    {
        if (ability.id == id)
            return &ability;
    }

    return nullptr;
}

std::vector<Ability> &Spellbook::getAbilities()
{
    return abilities_;
}

const std::vector<Ability> &Spellbook::getAbilities() const
{
    return abilities_;
}
