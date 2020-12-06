/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef PEON_HPP
#define PEON_HPP

// Project includes
#include "Victim.hpp"

class Peon : virtual public Victim
{
public:
    Peon(const std::string & name);
    ~Peon();

public:
    void getPolymorphed() const override;
};

#endif // PEON_HPP
