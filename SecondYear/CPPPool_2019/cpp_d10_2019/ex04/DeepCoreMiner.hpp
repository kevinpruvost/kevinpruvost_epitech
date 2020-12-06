/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef DEEPCOREMINER_HPP
#define DEEPCOREMINER_HPP

#include "IAsteroid.hpp"
#include "IMiningLaser.hpp"

class DeepCoreMiner : virtual public IMiningLaser
{
public:
    DeepCoreMiner();

public:
    void mine(IAsteroid *) override;
};

#endif // DEEPCOREMINER_HPP
