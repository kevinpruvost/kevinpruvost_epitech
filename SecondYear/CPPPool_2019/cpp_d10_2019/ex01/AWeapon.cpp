/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "AWeapon.hpp"

AWeapon::AWeapon(const std::string & name, int apcost, int damage)
    : _name { name }
    , _apcost { apcost }
    , _damage { damage }
{
}

AWeapon::~AWeapon()
{
}

const std::string & AWeapon::getName() const
{
    return _name;
}

int AWeapon::getAPCost() const
{
    return _apcost;
}

int AWeapon::getDamage() const
{
    return _damage;
}
