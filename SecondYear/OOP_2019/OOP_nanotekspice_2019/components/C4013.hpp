/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4013_HPP
#define C4013_HPP

// Project includes
#include "Factory.hpp"

class nts::C4013 : virtual public nts::Component
{
public:
    C4013(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;

private:
    nts::Tristate clock1 = nts::Tristate::UNDEFINED;
    nts::Tristate clock2 = nts::Tristate::UNDEFINED;
};

#endif // C4013_HPP
