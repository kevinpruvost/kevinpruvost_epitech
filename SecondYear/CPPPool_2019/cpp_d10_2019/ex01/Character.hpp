/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

// Project includes
#include "AWeapon.hpp"
#include "AEnemy.hpp"

// C++ includes
#include <string>
#include <iostream>

class Character
{
public:
    Character(const std::string & name);
    ~Character();

public:
    void recoverAP();
    void equip(AWeapon * weapon);
    void attack(AEnemy * enemy);
    const std::string & getName() const;
    const AWeapon * getWeapon() const;
    const int & getAP() const;

private:
    const std::string _name;
    AWeapon * _weapon = nullptr;
    int _ap;
};

std::ostream & operator<<(std::ostream & os, const Character & character);

#endif // CHARACTER_HPP
