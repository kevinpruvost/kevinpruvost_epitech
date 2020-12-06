/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef ASTEROKREOG_HPP
#define ASTEROKREOG_HPP

#include "IAsteroid.hpp"

class AsteroKreog : virtual public IAsteroid
{
public:
    AsteroKreog();

public:
    std::string beMined(const DeepCoreMiner * m) const override;
    std::string beMined(const StripMiner * m) const override;
    std::string getName() const override;
};

#endif // ASTEROKREOG_HPP
