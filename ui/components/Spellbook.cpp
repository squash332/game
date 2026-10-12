#include "Spellbook.hpp"

Spellbook::Spellbook() : spellbook_box_{0}
{
    spellbook_box_.height = VIRTUAL_HEIGHT * 2/3;
    spellbook_box_.width = VIRTUAL_WIDTH / 2;
    spellbook_box_.x = BTN_PADDING;
    spellbook_box_.y = spellbook_box_.height / 4;

    std:: cout <<"created spellbook !!"<< spellbook_box_.height << " "<< spellbook_box_.width << std::endl;
}

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
                .id = 1,
                .name = "Slash",
                .icon = LoadTexture("res/slash.png"),
                .description = "A quick melee attack that deals damage.",
                .damage = 20,
                .cooldown = 3.0f,
                .animType = AbilityAnim::Slash},

            Ability{
                .id = 2,
                .name = "Clap",
                .icon = LoadTexture("res/clap.png"),
                .description = "An AoE attack that deals damage to multiple enemies.",
                .damage = 10,
                .cooldown = 0.0f,
                .animType = AbilityAnim::Clap,
                .requiresTarget = false}};
        break;

    case PlayerClass::Mage:
        // todo
        break;

    case PlayerClass::Paladin:
        // todo
        break;
    }
}

void Spellbook::draw()
{

    // spellbook size: width, about a third of screen width, height : 2/3's of screen height, centered in the middle
    // draw texture that resembles a spellbook i guess ? sta
    DrawRectangleRec(spellbook_box_, COLOR_WINDOW_BG);
    
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
