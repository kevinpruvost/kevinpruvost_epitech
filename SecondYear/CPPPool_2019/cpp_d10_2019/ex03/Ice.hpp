/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class Ice : virtual public AMateria
{
public:
    Ice();

    AMateria * clone() const override;
    void use(ICharacter &target) override;

private:
};

#endif // ICE_HPP
