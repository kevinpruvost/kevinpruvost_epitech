/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4094_HPP
#define C4094_HPP

// Project includes
#include "Factory.hpp"

class nts::C4094 : virtual public nts::Component
{
public:
    C4094(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;

private:
    void noOutputHigh();
    void noOutputLow();
    void outputClockHigh();
    void outputClockLow();
};

#endif // C4094_HPP
