/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALASTEROID_HPP
#define KOALASTEROID_HPP

#include "IAsteroid.hpp"

class KoalaSteroid : virtual public IAsteroid
{
public:
    KoalaSteroid();

public:
    std::string beMined(const DeepCoreMiner * m) const override;
    std::string beMined(const StripMiner * m) const override;
    std::string getName() const override;
};

#endif // KOALASTEROID_HPP
