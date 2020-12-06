/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Cure.hpp"

#include <iostream>

Cure::Cure()
    : AMateria("cure")
{
}

AMateria * Cure::clone() const
{
    auto newice = new Cure;
    newice->setXP(getXP());
    return newice;
}

void Cure::use(ICharacter & target)
{
    std::cout << "* heals " << target.getName() << "\'s wounds *" << std::endl;
    setXP(getXP() + 10);
}
