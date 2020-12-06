/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Skat.hpp"

// C++ includes
#include <iostream>

Skat::Skat(const std::string & name, int stimPak)
    : _name { name }
    , _stimPaksNb { stimPak }
{
}

Skat::~Skat()
{
}

int Skat::stimPaks()
{
    return _stimPaksNb;
}

const std::string & Skat::name()
{
    return _name;
}

void Skat::shareStimPaks(int number, int & stock)
{
    if (number > _stimPaksNb)
    {
        std::cout << "Don't be greedy\n";
        return;
    }
    stock += number;
    _stimPaksNb -= number;
    std::cout << "Keep the change.\n";
}

void Skat::addStimPaks(unsigned int number)
{
    if (number == 0)
        std::cout << "Hey boya, did you forget something ?\n";
    _stimPaksNb += number;
}

void Skat::useStimPaks()
{
    if (_stimPaksNb <= 0)
    {
        std::cout << "Mediiiiiic\n";
        return;
    }
    std::cout << "Time to kick some ass and chew bubble gum.\n";
    --_stimPaksNb;
}

void Skat::status()
{
    std::cout << "Soldier " << _name << " reporting " << _stimPaksNb
              << " stimpaks remaining sir!\n";
}
