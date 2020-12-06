/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef POWERFIST_HPP
#define POWERFIST_HPP

// Project includes
#include "AWeapon.hpp"

class PowerFist : virtual public AWeapon
{
public:
    PowerFist();
    ~PowerFist() override;

public:
    void attack() const override;
};

#endif // POWERFIST_HPP
