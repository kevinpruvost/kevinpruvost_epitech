/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Mage.hpp"

Mage::Mage(const std::string & name, int level,
           const std::string & race,
           int pv, int power, int strength,
           int stamina, int intelligence, int spirit,
           int agility, const std::string & classs)
    : Character(name, level, classs, race, pv, power, strength,
                stamina, intelligence, spirit, agility, AttackRange::CLOSE)
{
    say("teleported");
}

int Mage::CloseAttack()
{
    if (Range != AttackRange::CLOSE)
        return 0;

    if (!checkAndUsePower(10))
        return 0;

    say("blinks");
    Range = AttackRange::RANGE;
    return 0;
}

int Mage::RangeAttack()
{
    if (Range != AttackRange::RANGE)
        return 0;

    if (!checkAndUsePower(25))
        return 0;

    const int dmg = 20 + _spirit;
    say("launches a fire ball");
    return dmg;
}

void Mage::RestorePower()
{
    setPower(getPower() + 50 + _intelligence);
    say("takes a mana potion");
    if (getPower() > 100)
        setPower(100);
}

void Mage::Heal()
{
    Character::Heal();
}
