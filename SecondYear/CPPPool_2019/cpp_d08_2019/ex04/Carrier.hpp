/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CARRIER_HPP
#define CARRIER_HPP

// Project includes
#include "Droid.hpp"

class Carrier
{
public:
    Carrier(const std::string id = "");
    ~Carrier();

public:
    std::string getId() const;
    size_t getEnergy() const;
    size_t getAttack() const;
    size_t getToughness() const;
    size_t getSpeed() const;
    Droid * const * getDroidList() const;
    Droid * getDroid(size_t index) const;

    void setId(const std::string & id);
    void setEnergy(size_t & energy);
    void setSpeed(size_t speed);
    bool addDroid(Droid * droid);
    Droid * popDroid();

    Carrier & operator<<(Droid * &oeuf);
    Carrier & operator<<(size_t & nrg);
    Carrier & operator>>(Droid * & oof);
    Carrier & operator~();
    bool operator()(const int x, const int y);

    Droid * operator [](int index) const;
    Droid * & operator [](int index);

private:
    std::string Id;
    size_t Energy = 300;
    const size_t MaxEnergy = 600;
    const size_t Attack = 100;
    const size_t Toughness = 90;
    size_t Speed = 0;
    Droid * Droids[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
};

std::ostream & operator<<(std::ostream & os, Carrier & c);

#endif // CARRIER_HPP
