/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#pragma once

// Project includes
#include "WarpSystem.hpp"
#include "Federation.hpp"

// C++ includes
#include <string>

class Borg::Ship : public ShipBase
{
public:
    Ship(int weaponFrequency = 20, short repair = 3);
    ~Ship();

public:
    void setupCore(WarpSystem::Core * core);
    void checkCore();

    int getWeaponFrequency();
    void setWeaponFrequency(int freq);

    void fire(Federation::Starfleet::Ship * target);
    void fire(Federation::Ship * target);
    void repair();

private:
    int _side;
    int _weaponFrequency;
    short _repair;

    WarpSystem::Core * _core = nullptr;
};
