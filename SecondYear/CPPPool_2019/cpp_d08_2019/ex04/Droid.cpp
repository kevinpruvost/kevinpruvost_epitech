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
    if (Status)
        delete Status;
    Status = droid.getStatus();
    BattleData->setExp(droid.getBattleData()->getExp());
    BattleData->setFingerprint(droid.getBattleData()->getFingerprint());
    std::cout << "Droid \'" << Id << "\'" << " Activated, Memory Dumped\n";
}

Droid::~Droid()
{
    if (Status)
        delete Status;
    if (BattleData)
        delete BattleData;
    std::cout << "Droid \'" << Id << "\' Destroyed\n";
}

Droid & Droid::operator=(const Droid & droid)
{
    Id = droid.getId();
    if (Status)
        delete Status;
    Status = droid.getStatus();
    BattleData->setExp(droid.getBattleData()->getExp());
    BattleData->setFingerprint(droid.getBattleData()->getFingerprint());
    return *this;
}

bool Droid::operator==(const Droid & droid) const
{
    const auto cmp1 = getStatus();
    const auto cmp2 = droid.getStatus();
    bool res = true;

    if (!cmp1 || !cmp2)
    {
        if (cmp1) delete cmp1;
        if (cmp2) delete cmp2;
        return false;
    }
    if (*cmp1 != *cmp2)
        res = false;
    delete cmp1;
    delete cmp2;
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

std::ostream & operator<<(std::ostream & os, Droid & droid)
{
    if (droid._msg == 0)
    {
        os << 0;
        return os;
    }
    const auto str = droid.getStatus();
    if (!str)
        return os;
    os << "Droid \'" << droid.getId() << "\', " << str->c_str()
       << ", " << droid.getEnergy();
    delete str;
    return os;
}

std::ostream & operator<<(std::ostream & os, Droid * droidd)
{
    auto & droid = *droidd;
    const auto str = droid.getStatus();
    if (!str)
        return os;
    os << "Droid \'" << droid.getId() << "\', " << str->c_str()
       << ", " << droid.getEnergy();
    delete str;
    return os;
}

bool Droid::operator()(const std::string * task, const size_t minExp)
{
    if (Energy <= 10)
    {
        setStatus(new std::string("Battery Low"));
        Energy = 0;
        return false;
    }
    const auto battleData = getBattleData();
    std::string str = *task;
    if (getBattleData()->getExp() < minExp)
    {
        str.append(" - Failed!");
        setStatus(new std::string(str));
        Energy -= 10;
        battleData->setExp(battleData->getExp() + minExp);
        return false;
    }
    str.append(" - Completed!");
    setStatus(new std::string(str));
    Energy -= 10;
    battleData->setExp(battleData->getExp() + (minExp/2));
    return true;
}

Droid * Droid::operator *()
{
    return this;
}

Droid & Droid::operator=(const int & id)
{
    _msg = id;
    return *this;
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

DroidMemory * Droid::getBattleData() const
{
    return BattleData;
}

void Droid::setBattleData(DroidMemory * battleData)
{
    if (!battleData)
        return;
    if (BattleData)
        delete BattleData;
    BattleData = battleData;
}
