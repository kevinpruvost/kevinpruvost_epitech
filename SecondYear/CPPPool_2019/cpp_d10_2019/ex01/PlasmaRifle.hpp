/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PLASMARIFLE_HPP
#define PLASMARIFLE_HPP

// Project includes
#include "AWeapon.hpp"

class PlasmaRifle : virtual public AWeapon
{
public:
    PlasmaRifle();
    ~PlasmaRifle() override;

public:
    void attack() const override;
};

#endif // PLASMARIFLE_HPP
