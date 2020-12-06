/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "MiningBarge.hpp"

#include <cstddef>

MiningBarge::MiningBarge()
{
    for (size_t i = 0; i < 4; ++i)
        _lasers[i] = nullptr;
}

void MiningBarge::equip(IMiningLaser *laser)
{
    if (!laser)
        return;
    for (size_t i = 0 ; i < 4; ++i)
    {
        if (!_lasers[i])
        {
            _lasers[i] = laser;
            return;
        }
    }
}

void MiningBarge::mine(IAsteroid *aster) const
{
    if (!aster)
        return;
    for (size_t i = 0; i < 4; ++i)
    {
        if (_lasers[i])
            _lasers[i]->mine(aster);
    }
}
