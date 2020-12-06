/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "StripMiner.hpp"

#include <iostream>

StripMiner::StripMiner()
{
}

void StripMiner::mine(IAsteroid * aster)
{
    if (!aster)
        return;
    std::cout << "* strip mining... got " << aster->beMined(this) << " ! *" << std::endl;
}
