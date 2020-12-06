/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Droid.hpp"

// C++ includes
#include <iostream>

Droid::Droid(const std::string && serial)
    : Id { serial }
{
    std::cout << "Droid \'" << serial << "\'" << " Activated\n";
}

Droid::Droid(const std::string & serial)
    : Id { serial }
{
    std::cout << "Droid \'" << serial << "\'" << " Activated\n";
}

Droid::Droid(const Droid & droid)
    : Id { droid.getId() }
{
    Id = droid.getId();
    Energy = droid.getEnergy();
    Status = droid.getStatus();
    std::cout << "Droid \'" << Id << "\'" << " Activated, Memory Dumped\n";
}

Droid::~Droid()
{
    if (Status)
        delete Status;
    std::cout << "Droid \'" << Id << "\' Destroyed\n";
}

Droid & Droid::operator=(const Droid & otherDroid)
{
    Id = otherDroid.getId();
    Energy = otherDroid.getEnergy();
    Status = otherDroid.getStatus();
    return *this;
}

bool Droid::operator==(const Droid & droid) const
{
    if (getId()        != droid.getId())
        return false;
    if (getEnergy()    != droid.getEnergy())
        return false;
    if (getAttack()    != droid.getAttack())
        return false;
    if (getToughness() != droid.getToughness())
        return false;
    const auto stat1 = getStatus();
    const auto stat2 = droid.getStatus();
    bool res = true;
    if (*stat1 != *stat2)
        res = false;
    delete stat1;
    delete stat2;
    return res;
}

bool Droid::operator!=(const Droid & droid) const
{
    if (operator==(droid))
        return false;
    return true;
}

void Droid::operator<<(size_t & nb)
{
    size_t plusvalueMax = 100 - Energy;

    if (plusvalueMax == 0)
        return;
    if (nb >= plusvalueMax)
    {
        nb -= plusvalueMax;
        Energy = 100;
    }
    else
    {
        Energy += nb;
        nb = 0;
    }
}

std::ostream & operator<<(std::ostream & os, const Droid & droid)
{
    os << "Droid \'" << droid.getId() << "\', " << droid.getStatus()->c_str()
       << ", " << droid.getEnergy();
    return os;
}

// Getters, setters ------------------------------------------------------------

std::string Droid::getId() const
{
    return Id;
}

size_t Droid::getEnergy() const
{
    return Energy > 100 ? 100 : Energy;
}

std::string * Droid::getStatus() const
{
    return new std::string(Status->c_str());
}

size_t Droid::getAttack() const
{
    return Attack;
}

size_t Droid::getToughness() const
{
    return Toughness;
}

void Droid::setId(const std::string & serial)
{
    Id = serial;
}

void Droid::setEnergy(const size_t energy)
{
    Energy = energy;
    if (Energy > 100)
        Energy = 100;
}

void Droid::setStatus(std::string * status)
{
    if (!status)
        return;
    if (Status)
        delete Status;
    Status = status;
}
