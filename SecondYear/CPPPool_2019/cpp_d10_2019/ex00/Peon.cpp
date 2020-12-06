/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Peon.hpp"

Peon::Peon(const std::string & name)
    : Victim(name)
{
    std::cout << "Zog zog.\n";
}

Peon::~Peon()
{
    std::cout << "Bleuark...\n";
}

void Peon::getPolymorphed() const
{
    std::cout << getName() << " has been turned into a pink pony!\n";
}
