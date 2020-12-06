/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Hunter.hpp"

Hunter::Hunter(const std::string & name, int level,
               const std::string & weapon, const std::string race,
               int pv, int power, int strength,
               int stamina, int intelligence, int spirit,
               int agility, const std::string & classs)
    : Character(name, level, classs, race, pv, power, strength,
                stamina, intelligence, spirit, agility, AttackRange::CLOSE)
    , Warrior(name, level, weapon, race, classs, pv, power, strength, stamina,
              intelligence, spirit, agility)
{
    say("is born from a tree");
}

int Hunter::RangeAttack()
{
    if (Range != AttackRange::RANGE)
        return 0;

    if (!checkAndUsePower(25))
        return 0;

    const int dmg = 20 + _agility;
    say("uses his bow");
    return dmg;
}

int Hunter::CloseAttack()
{
    return Warrior::CloseAttack();
}

void Hunter::Heal()
{
    Character::Heal();
}

void Hunter::RestorePower()
{
    setPower(100);
    say("meditates");
}
