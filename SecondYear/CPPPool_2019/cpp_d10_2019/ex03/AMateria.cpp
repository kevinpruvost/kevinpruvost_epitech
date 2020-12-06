/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "AMateria.hpp"

#include <iostream>

AMateria::AMateria(const std::string & type)
    : type_ { type }
{

}

AMateria::~AMateria()
{
}

const std::string & AMateria::getType() const
{
    return type_;
}

unsigned int AMateria::getXP() const
{
    return xp_;
}

void AMateria::setXP(unsigned int xp)
{
    xp_ = xp;
}

void AMateria::use(ICharacter &target)
{
    (void)target;
    xp_ += 10;
}
