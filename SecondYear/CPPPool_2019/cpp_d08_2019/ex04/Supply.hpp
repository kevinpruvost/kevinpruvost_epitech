/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SUPPLY_HPP
#define SUPPLY_HPP

// Project includes
#include "Carrier.hpp"

class Supply
{
public:
    enum Types
    {
        Iron = 1,
        Silicon = 2,
        Wreck = 3
    };

public:
    Supply(Types type, size_t amount);
    Supply(Types type, size_t amount, Droid ** wrecks);
    ~Supply();

public:
    Droid & operator*();
    Supply & operator++();
    Supply & operator--();
//    Supply & operator->();
    Droid * operator->();
    operator size_t();
    Supply & operator!();
    bool operator==(const Supply & supply) const;
    bool operator==(const Types & type) const;
    bool operator!=(const Supply & supply) const;
    bool operator!=(const Types & type) const;

public:
    size_t getWrecksSize() const;
    Types getType() const;
    size_t getAmount() const;
    int getIndex() const;
    Droid ** getWrecks() const;
    Droid * getWreck(size_t index) const;

    void setType(Types type);
    void setAmount(size_t amount);
    void setWrecks(Droid ** wrecks);
    void setIndex(int id);

private:
    Types Type;
    size_t Amount;
    Droid ** Wrecks;
    int index = 0;
};

std::ostream & operator<<(std::ostream & os, Supply & supply);

#endif // SUPPLY_HPP
