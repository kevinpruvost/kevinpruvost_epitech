/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef STRIPMINER_HPP
#define STRIPMINER_HPP

#include "IAsteroid.hpp"
#include "IMiningLaser.hpp"

class StripMiner : virtual public IMiningLaser
{
public:
    StripMiner();

public:
    void mine(IAsteroid *) override;
};

#endif // STRIPMINER_HPP
