/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SUPERMUTANT_HPP
#define SUPERMUTANT_HPP

// Project includes
#include "AEnemy.hpp"

class SuperMutant : virtual public AEnemy
{
public:
    SuperMutant();
    ~SuperMutant() override;

public:
    void takeDamage(int damage) override;
};

#endif // SUPERMUTANT_HPP
