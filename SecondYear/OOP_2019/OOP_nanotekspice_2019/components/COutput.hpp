/*
** EPITECH PROJECT, 2020
** COutput.hpp
** File description:
** c output
*/

#pragma once

// Project includes
#include "Factory.hpp"

class nts::COutput : virtual public nts::Component
{
public:
    COutput(const std::string & name);
    void dump() const override;
    std::string display() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    nts::Tristate computeOutput() override;
    void prepare() override;
    nts::ComponentType getComponentType() const override; 
};
