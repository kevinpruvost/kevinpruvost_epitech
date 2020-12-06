/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Ice.hpp"

#include <iostream>

Ice::Ice()
    : AMateria("ice")
{
}

AMateria * Ice::clone() const
{
    auto newice = new Ice;
    newice->setXP(getXP());
    return newice;
}

void Ice::use(ICharacter & target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
    setXP(getXP() + 10);
}
