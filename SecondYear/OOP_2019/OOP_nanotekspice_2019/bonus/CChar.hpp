/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef CChar_HPP
#define CChar_HPP

// Project includes
#include "../components/Factory.hpp"

class nts::CChar : virtual public nts::Component
{
public:
    CChar(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;

private:
    void printChar() const;
};

#endif
