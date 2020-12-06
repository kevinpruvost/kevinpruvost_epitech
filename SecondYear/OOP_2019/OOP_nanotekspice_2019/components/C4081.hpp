/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4081_HPP
#define C4081_HPP

// Project includes
#include "Factory.hpp"

class nts::C4081 : virtual public nts::Component
{
public:
    C4081(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;
};

#endif // C4081_HPP
