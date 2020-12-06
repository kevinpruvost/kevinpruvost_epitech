/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "KoalaSteroid.hpp"

#include <iostream>

KoalaSteroid::KoalaSteroid()
{
}

std::string KoalaSteroid::beMined(const StripMiner *m) const
{
    (void)m;
    return "Koalite";
}

std::string KoalaSteroid::beMined(const DeepCoreMiner *m) const
{
    (void)m;
    return "Zazium";
}

std::string KoalaSteroid::getName() const
{
    return "KoalaSteroid";
}
