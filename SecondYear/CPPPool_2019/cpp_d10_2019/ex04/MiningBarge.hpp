/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef MININGBARGE_HPP
#define MININGBARGE_HPP

#include "DeepCoreMiner.hpp"
#include "StripMiner.hpp"

class MiningBarge
{
public:
    MiningBarge();

public:
    void equip(IMiningLaser * laser);
    void mine(IAsteroid * aster) const;

private:
    IMiningLaser * _lasers[4] = { nullptr, nullptr, nullptr, nullptr };
};

#endif // MININGBARGE_HPP
