/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Warrior.hpp"

// C++ includes
#include <iostream>

Warrior::Warrior(const std::string & name, int level,
                 const std::string & weaponName,
                 const std::string race, const std::string & classs,
                 int pv, int power, int strength,
                 int stamina, int intelligence, int spirit,
                 int agility)
    : Character(name, level, classs, race, pv, power, strength,
                stamina, intelligence, spirit, agility, AttackRange::CLOSE)
    , _weaponName { weaponName }
{
    std::string str("I'm ");
    str.append(name);
    str.append(" KKKKKKKKKKRRRRRRRRRRRRRREEEEEEEEOOOOOOORRRRGGGGGGG");
    std::cout << str << std::endl;
}

int Warrior::CloseAttack()
{
    if (Range != AttackRange::CLOSE)
        return 0;

    if (!checkAndUsePower(30))
        return 0;

    const int dmg = 20 + _strength;
    std::string str("strikes with his ");
    str.append(_weaponName);
    say(str);
    return dmg;
}

int Warrior::RangeAttack()
{
    if (Range != AttackRange::RANGE)
        return 0;

    if (!checkAndUsePower(10))
        return 0;

    say("intercepts");
    Range = AttackRange::CLOSE;
    return 0;
}

void Warrior::Heal()
{
    Character::Heal();
}

void Warrior::RestorePower()
{
    Character::RestorePower();
}
