/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "DeepCoreMiner.hpp"

#include <iostream>

DeepCoreMiner::DeepCoreMiner()
{

}

void DeepCoreMiner::mine(IAsteroid * aster)
{
    if (!aster)
        return;
    std::cout << "* mining deep... got " << aster->beMined(this) << " ! *" << std::endl;
}
