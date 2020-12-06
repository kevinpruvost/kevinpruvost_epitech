/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4071_HPP
#define C4071_HPP

// Project includes
#include "Factory.hpp"

class nts::C4071 : virtual public nts::Component
{
public:
    C4071(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;
};

#endif // C4071_HPP
