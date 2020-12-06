/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4514_HPP
#define C4514_HPP

// Project includes
#include "Factory.hpp"

class nts::C4514 : virtual public nts::Component
{
public:
    C4514(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;
};

#endif // C4514_HPP
