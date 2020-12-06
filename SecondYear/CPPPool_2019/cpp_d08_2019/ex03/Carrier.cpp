/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Carrier.hpp"

Carrier::Carrier(const std::string id)
    : Id { id }
{
}

Carrier::~Carrier()
{
    for (size_t index = 0; index < 5; ++index)
    {
        if (Droids[index])
            delete Droids[index];
    }
}

Carrier & Carrier::operator<<(Droid * & droid)
{
    if (addDroid(droid))
        droid = nullptr;
    size_t length = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        if (Droids[i])
            ++length;
    }
    if (length == 0)
        Speed = 0;
    else
        Speed = 100 - (10 * length);
    return *this;
}

Carrier & Carrier::operator>>(Droid * & droid)
{
    for (size_t i = 0; i < 5; ++i)
    {
        if (Droids[i])
        {
            droid = Droids[i];
            Droids[i] = nullptr;
            size_t length = 0;
            for (size_t i = 0; i < 5; ++i)
            {
                if (Droids[i])
                    ++length;
            }
            if (length == 0)
                Speed = 0;
            else
                Speed = 100 - (10 * length);
            return *this;
        }
    }
    return *this;
}

Carrier & Carrier::operator<<(size_t & nrg)
{
    if (Energy >= MaxEnergy)
        return *this;

    size_t canFill = MaxEnergy - Energy;
    if (canFill == 0)
        return *this;
    if (canFill >= nrg)
    {
        Energy += nrg;
        nrg = 0;
    }
    else
    {
        Energy = MaxEnergy;
        nrg -= canFill;
    }
    return *this;
}

Droid * Carrier::operator[](int index) const
{
    return Droids[index];
}

Droid * & Carrier::operator[](int index)
{
    return Droids[index];
}

Carrier & Carrier::operator~()
{
    size_t length = 0;
    for (size_t i = 0; i < 5; ++i)
    {
        if (Droids[i])
            ++length;
    }
    if (length == 0)
        Speed = 0;
    else
        Speed = 100 - (10 * length);
    return *this;
}

bool Carrier::operator()(const int x, const int y)
{
    if (Speed == 0)
        return false;

    int nbDroid = 0;
    for (size_t i = 0; i < 5; ++i)
        if (Droids[i])
            ++nbDroid;
    size_t cost = (abs(x) + abs(y)) * (10 + nbDroid);
    if (cost > Energy)
        return false;
    Energy -= cost;
    return true;
}

// Write -----------------------------------------------------------------------

std::ostream & operator<<(std::ostream & os, Carrier & c)
{
    os << "Carrier \'" << c.getId() << "\' Droid(s) on-board:\n";
    for (size_t i = 0; i < 5; ++i)
    {
        os << "[" << i << "] : ";
        if (!c.getDroid(i))
            os << "Free";
        else
            os << *(c.getDroid(i));
        os << std::endl;
    }
    os << "Speed : " << c.getSpeed() << ", Energy " << c.getEnergy();
    return os;
}

// Getters and setters ---------------------------------------------------------

std::string Carrier::getId() const { return Id; }

size_t Carrier::getEnergy() const { return Energy; }

size_t Carrier::getAttack() const { return Attack; }

size_t Carrier::getToughness() const { return Toughness; }

size_t Carrier::getSpeed() const { return Speed; }

Droid * const * Carrier::getDroidList() const { return Droids; }

Droid * Carrier::getDroid(size_t index) const { return Droids[index]; }

void Carrier::setId(const std::string & id) { Id = id; }

void Carrier::setEnergy(size_t & energy)
{
    Energy = energy;
    if (Energy > 100)
        Energy = 100;
}

void Carrier::setSpeed(size_t speed) { Speed = speed; }

bool Carrier::addDroid(Droid * droid)
{
    for (size_t index = 0; index < 5; ++index)
    {
        if (Droids[index] == droid)
            return false;
        if (!Droids[index])
        {
            Droids[index] = droid;
            return true;
        }
    }
    return false;
}

Droid * Carrier::popDroid()
{
    for (int index = 4; index >= 0; --index)
    {
        if (Droids[index])
        {
            const auto stock = Droids[index];
            Droids[index] = nullptr;
            return stock;
        }
    }
    return nullptr;
}
