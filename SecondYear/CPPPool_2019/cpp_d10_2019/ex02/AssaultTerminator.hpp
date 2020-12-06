/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef ASSAULTTERMINATOR_HPP
#define ASSAULTTERMINATOR_HPP

// Project includes
#include "ISpaceMarine.hpp"

class AssaultTerminator : virtual public ISpaceMarine
{
public:
    AssaultTerminator();
    ~AssaultTerminator() override;

public:
    ISpaceMarine * clone() const override;
    void battleCry() const override;
    void rangedAttack() const override;
    void meleeAttack() const override;
};

#endif // ASSAULTTERMINATOR_HPP
