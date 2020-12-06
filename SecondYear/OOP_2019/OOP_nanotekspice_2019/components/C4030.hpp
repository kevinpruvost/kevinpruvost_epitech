/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef C4030_HPP
#define C4030_HPP

#include "Factory.hpp"

class nts::C4030 : virtual public nts::Component
{
public:
    C4030(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;
};

#endif // C4030_HPP
