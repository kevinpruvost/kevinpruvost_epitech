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

// C++ includes
#include <string>
#include <ostream>

class Droid
{
public:
    Droid(const std::string & serial);
    Droid(const std::string && serial = "");
    Droid(const Droid & droid);
    ~Droid();

public:
    Droid & operator=(const Droid & otherDroid);
    bool operator==(const Droid & droid2) const;
    bool operator!=(const Droid & droid2) const;

    void operator<<(size_t & nb);

public:
    std::string getId() const;
    size_t getEnergy() const;
    std::string * getStatus() const;
    size_t getAttack() const;
    size_t getToughness() const;

    void setId(const std::string & serial);
    void setEnergy(const size_t energy);
    void setStatus(std::string * status);

private:
    std::string Id;
    size_t      Energy = 50;
    const size_t Attack = 25;
    const size_t Toughness = 15;
    std::string * Status = new std::string("Standing by");
};

std::ostream & operator<<(std::ostream & os, const Droid & droid);

#endif // DROID_HPP
