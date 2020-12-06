/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef HUNTER_HPP
#define HUNTER_HPP

// Project includes
#include "Warrior.hpp"

class Hunter : private Warrior, virtual public Character
{
public:
    Hunter(const std::string & name = "Fourdr", int level = 40,
           const std::string & weapon = "sword",
            const std::string race = "Elf",
            int pv = 100, int power = 100, int strength = 9,
            int stamina = 9, int intelligence = 5, int spirit = 6,
            int agility = 25, const std::string & classs = "Hunter");

public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();
};

#endif // HUNTER_HPP
