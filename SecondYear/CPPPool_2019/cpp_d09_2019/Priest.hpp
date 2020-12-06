/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PRIEST_HPP
#define PRIEST_HPP

// Project includes
#include "Mage.hpp"

class Priest : virtual public Mage
{
public:
    Priest(const std::string & name = "Iopi", int level = 84, const std::string race = "Orc",
           int pv = 100, int power = 100, int strength = 4,
           int stamina = 4, int intelligence = 42, int spirit = 21,
           int agility = 2, const std::string & classs = "Priest");

public:
    int CloseAttack();
    int RangeAttack();
    void Heal();
    void RestorePower();
};

#endif // PRIEST_HPP
