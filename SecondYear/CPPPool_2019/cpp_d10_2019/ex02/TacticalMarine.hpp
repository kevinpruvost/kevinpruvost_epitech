/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef TACTICALMARINE_HPP
#define TACTICALMARINE_HPP

// Project includes
#include "ISpaceMarine.hpp"

class TacticalMarine : virtual public ISpaceMarine
{
public:
    TacticalMarine();
    ~TacticalMarine() override;

public:
    ISpaceMarine * clone() const override;
    void battleCry() const override;
    void rangedAttack() const override;
    void meleeAttack() const override;
};

#endif // TACTICALMARINE_HPP
