/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PALADIN_HPP
#define PALADIN_HPP

// Project includes
#include "Warrior.hpp"
#include "Priest.hpp"

class Paladin : virtual public Warrior, Priest
{
public:
    Paladin(const std::string & name = "Phiste", int level = 42,
            const std::string & weapon = "hammer",
            const std::string race = "Human",
            int pv = 100, int power = 100, int strength = 9,
            int stamina = 10, int intelligence = 10, int spirit = 10,
            int agility = 2, const std::string & classs = "Paladin");

public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();

    int Intercept();
};

#endif // PALADIN_HPP
