/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef WARRIOR_HPP
#define WARRIOR_HPP

// Project includes
#include "Character.hpp"

class Warrior : virtual public Character
{
public:
    Warrior(const std::string & name = "Thor", int level = 42,
            const std::string & weaponName = "hammer",
            const std::string race = "Dwarf",
            const std::string & classs = "Warrior",
            int pv = 100, int power = 100, int strength = 12,
            int stamina = 12, int intelligence = 6, int spirit = 5,
            int agility = 7);
public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();

private:
    const std::string _weaponName;
};

#endif // WARRIOR_HPP
