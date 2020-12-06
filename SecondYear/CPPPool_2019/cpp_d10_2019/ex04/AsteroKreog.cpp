/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "AsteroKreog.hpp"

AsteroKreog::AsteroKreog()
{

}

std::string AsteroKreog::beMined(const StripMiner *m) const
{
    (void)m;
    return "Kreogium";
}

std::string AsteroKreog::beMined(const DeepCoreMiner *m) const
{
    (void)m;
    return "Sullite";
}

std::string AsteroKreog::getName() const
{
    return "AsteroKreog";
}
