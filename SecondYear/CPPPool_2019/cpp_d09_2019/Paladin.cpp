/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Paladin.hpp"

// C++ includes
#include <iostream>

Paladin::Paladin(const std::string & name, int level,
                 const std::string & weapon,
                 const std::string race,
                 int pv, int power, int strength,
                 int stamina, int intelligence, int spirit,
                 int agility, const std::string & classs)
    : Character(name, level, classs, race, pv, power, strength, stamina,
                intelligence, spirit, agility, AttackRange::CLOSE)
    , Warrior(name, level, weapon, race, classs, pv, power, strength, stamina,
              intelligence, spirit, agility)
    , Priest(name, level, race, pv, power, strength, stamina,
                intelligence, spirit, agility, classs)
{
    std::string str("the light falls on ");
    str.append(getName());
    std::cout << str << std::endl;
}

int Paladin::RangeAttack()
{
    return Priest::RangeAttack();
}

int Paladin::CloseAttack()
{
    return Warrior::CloseAttack();
}

void Paladin::Heal()
{
    Priest::Heal();
}

void Paladin::RestorePower()
{
    Warrior::RestorePower();
}

int Paladin::Intercept()
{
    return Warrior::RangeAttack();
}
