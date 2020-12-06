/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef IASTEROID_HPP
#define IASTEROID_HPP

class StripMiner;
class DeepCoreMiner;

#include <string>

class IAsteroid
{
public:
    virtual ~IAsteroid() {}

    virtual std::string beMined(const StripMiner * m) const = 0;
    virtual std::string beMined(const DeepCoreMiner * m) const = 0;
    virtual std::string getName() const = 0;
};

#endif // IASTEROID_HPP
