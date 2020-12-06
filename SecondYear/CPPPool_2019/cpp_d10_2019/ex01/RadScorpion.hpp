/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef RADSCORPION_HPP
#define RADSCORPION_HPP

// Project includes
#include "AEnemy.hpp"

class RadScorpion : virtual public AEnemy
{
public:
    RadScorpion();
    ~RadScorpion() override;
};

#endif // RADSCORPION_HPP
