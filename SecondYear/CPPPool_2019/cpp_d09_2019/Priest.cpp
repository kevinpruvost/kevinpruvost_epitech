/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Priest.hpp"

Priest::Priest(const std::string & name, int level,
           const std::string race,
           int pv, int power, int strength,
           int stamina, int intelligence, int spirit,
           int agility, const std::string & classs)
    : Character(name, level, classs, race, pv, power, strength, stamina,
            intelligence, spirit, agility, AttackRange::CLOSE)
    , Mage(name, level, race, pv, power, strength, stamina,
           intelligence, spirit, agility, classs)
{
    say("enters in the order");
}

int Priest::RangeAttack()
{
    return Mage::RangeAttack();
}

int Priest::CloseAttack()
{
    if (Range != AttackRange::CLOSE)
        return 0;

    if (!checkAndUsePower(10))
        return 0;

    say("uses a spirit explosion");
    Range = AttackRange::RANGE;
    return 10 + getSpirit();
}

void Priest::Heal()
{
    if (!checkAndUsePower(10))
        return;

    setPv(getPv() + 70);
    if (getPv() > 100)
        setPv(100);

    say("casts a little heal spell");
}

void Priest::RestorePower()
{
    Mage::RestorePower();
}
