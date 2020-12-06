/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CURE_HPP
#define CURE_HPP

#include "AMateria.hpp"

class Cure : virtual public AMateria
{
public:
    Cure();

public:
    AMateria * clone() const override;
    void use(ICharacter & target) override;
};

#endif // CURE_HPP
