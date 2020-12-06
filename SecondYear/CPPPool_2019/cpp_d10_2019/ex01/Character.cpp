/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Character.hpp"

Character::Character(const std::string & name)
    : _name { name }
    , _weapon { nullptr }
    , _ap { 40 }
{
}

Character::~Character()
{
}

void Character::recoverAP()
{
    _ap += 10;
    if (_ap > 40)
        _ap = 40;
}

void Character::equip(AWeapon * weapon)
{
    if (!weapon)
        return;
    _weapon = weapon;
}

void Character::attack(AEnemy * enemy)
{
    if (!enemy || !_weapon)
        return;

    if (_ap < _weapon->getAPCost() || _ap < 0)
        return;

    std::cout << _name << " attacks " << enemy->getType() << " with a "
              << _weapon->getName() << std::endl;

    _ap -= _weapon->getAPCost();
    if (_ap < 0)
        _ap = 0;
    _weapon->attack();
    enemy->takeDamage(_weapon->getDamage());
    if (enemy->getHP() <= 0)
    {
        delete enemy;
        enemy = nullptr;
    }
}

// Getters and setters ---------------------------------------------------------

const std::string & Character::getName() const { return _name; }

const AWeapon * Character::getWeapon() const { return _weapon; }

const int & Character::getAP() const { return _ap; }

// Stand-alone operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, const Character & character)
{
    if (character.getWeapon() == nullptr)
    {
        os << character.getName() << " has " << character.getAP()
           << " AP and is unarmed" << std::endl;
    }
    else
    {
        os << character.getName() << " has " << character.getAP()
           << " AP and wields a " << character.getWeapon()->getName()
           << std::endl;
    }
    return os;
}
