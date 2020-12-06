/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "AEnemy.hpp"

AEnemy::AEnemy(int hp, const std::string & type)
    : _hp { hp }
    , _type { type }
{
}

AEnemy::~AEnemy()
{
}

// Getters and setters ---------------------------------------------------------

const std::string & AEnemy::getType() const
{
    return _type;
}

int AEnemy::getHP() const
{
    return _hp;
}

void AEnemy::setHP(int hp)
{
    _hp = hp;
}

void AEnemy::takeDamage(int damage)
{
    if (damage < 0)
        return;
    setHP(_hp - damage);
}
