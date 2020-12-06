/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef AWEAPON_HPP
#define AWEAPON_HPP

// C++ includes
#include <string>

class AWeapon
{
public:
    AWeapon(const std::string & name, int apcost, int damage);
    virtual ~AWeapon();

public:
    const std::string & getName() const;
    int getAPCost() const;
    int getDamage() const;
    virtual void attack() const = 0;

private:
    const std::string _name;
    int _apcost;
    int _damage;
};

#endif // AWEAPON_HPP
