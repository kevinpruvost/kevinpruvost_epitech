/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Phaser.hpp"

// C++ includes
#include <iostream>

Phaser::Phaser(int maxAmmo, AmmoType type)
    : _maxAmmo  { maxAmmo }
    , _type     { type    }
    , _typeBase { type    }
{
    _ammo[type] = maxAmmo;
}

Phaser::~Phaser()
{
}

void Phaser::fire()
{
    if (_maxAmmo > 0)
    {
        std::string sound;
        if (_type == AmmoType::REGULAR)
            sound = Sounds::Regular;
        if (_type == AmmoType::PLASMA)
            sound = Sounds::Plasma;
        if (_type == AmmoType::ROCKET)
            sound = Sounds::Rocket;
        std::cout << sound << std::endl;
        --_ammo[_type];
    }
    else
    {
        std::cout << "Clip empty, please reload\n";
    }
}

void Phaser::ejectClip()
{
    _ammo[_type] = 0;
}

void Phaser::changeType(AmmoType type)
{
    std::string typeStr;
    if (type == AmmoType::REGULAR)
        typeStr = "regular";
    if (type == AmmoType::PLASMA)
        typeStr = "plasma";
    if (type == AmmoType::ROCKET)
        typeStr = "rocket";
    std::cout << "Switching ammo to type: " << typeStr << std::endl;
    _type = type;
}

void Phaser::reload()
{
    std::cout << "Reloading ...\n";
    _type = _typeBase;
    _ammo[_type] = _maxAmmo;
}

void Phaser::addAmmo(AmmoType type)
{
    if (_ammo[type] >= _maxAmmo)
        std::cout << "Clip full\n";
    _ammo[type] += 1;
}

int Phaser::getCurrentAmmos()
{
    return _ammo[_type];
}
