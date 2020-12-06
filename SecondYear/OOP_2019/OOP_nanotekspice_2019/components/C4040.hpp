/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef C4040_HPP
#define C4040_HPP

// Project includes
#include "Factory.hpp"

class nts::C4040 : virtual public nts::Component
{
public:
    C4040(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void prepare() override;

private:
    void resetCount();
    void addCount();
    void setCount(size_t count);
    size_t readCount() const;
};

#endif // C4040_HPP
