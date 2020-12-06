/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/22
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef DROID_HPP
#define DROID_HPP

// Project includes
#include "DroidMemory.hpp"

// C++ includes
#include <string>
#include <ostream>

class Droid
{
public:
    Droid(const std::string & serial);
    Droid(const std::string && serial);
    Droid(const Droid & droid);
    ~Droid();

public:
    Droid & operator=(const Droid & otherDroid);
    bool operator==(const Droid & droid2) const;
    bool operator!=(const Droid & droid2) const;

    bool operator()(const std::string * task, const size_t minExp);

    void operator<<(size_t & nb);

    Droid * operator*();

    Droid & operator=(const int & id);

public:
    std::string getId() const;
    size_t getEnergy() const;
    std::string * getStatus() const;
    size_t getAttack() const;
    size_t getToughness() const;
    DroidMemory * getBattleData() const;

    void setId(const std::string & serial);
    void setEnergy(const size_t energy);
    void setStatus(std::string * status);
    void setBattleData(DroidMemory * battleData);

    int _msg = 1;
private:
    std::string   Id;
    size_t        Energy = 50;
    const size_t  Attack = 25;
    const size_t  Toughness = 15;
    std::string * Status = new std::string("Standing by");
    DroidMemory * BattleData = new DroidMemory;
};

std::ostream & operator<<(std::ostream & os, Droid & droid);
std::ostream & operator<<(std::ostream & os, Droid * droid);

#endif // DROID_HPP
