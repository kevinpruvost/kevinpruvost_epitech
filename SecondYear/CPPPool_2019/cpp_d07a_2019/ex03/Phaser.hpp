/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PHASER_HPP
#define PHASER_HPP

// Project includes
#include "Sounds.hpp"

class Phaser
{
public:
    enum AmmoType
    {
        REGULAR = 0,
        PLASMA = 1,
        ROCKET = 2
    };

    Phaser(int maxAmmo = 20, AmmoType type = REGULAR);
    ~Phaser();

    void fire();
    void ejectClip();
    void changeType(AmmoType type);
    void reload();
    void addAmmo(AmmoType type);
    int getCurrentAmmos();

private:
    static const int Empty = 0;
    int _maxAmmo;

    int _ammo[3];
    AmmoType _type;
    AmmoType _typeBase;
};

#endif // PHASER_HPP
