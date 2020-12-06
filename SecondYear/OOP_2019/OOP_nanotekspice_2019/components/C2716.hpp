/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C2716_HPP
#define C2716_HPP

// Project includes
#include "Factory.hpp"

class nts::C2716 : virtual public nts::Component
{
public:
    C2716(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;
};

#endif // C2716_HPP
