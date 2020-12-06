/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef MAGE_HPP
#define MAGE_HPP

// Project includes
#include "Character.hpp"

class Mage : virtual public Character
{
public:
    Mage(const std::string & name = "Fluffy", int level = 40,
         const std::string & race = "Gnome",
         int pv = 100, int power = 100, int strength = 6,
         int stamina = 6, int intelligence = 12, int spirit = 11,
         int agility = 7, const std::string & classs = "Mage");

public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();

private:
};

#endif // MAGE_HPP
