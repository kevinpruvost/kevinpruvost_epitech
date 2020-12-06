/*
** EPITECH PROJECT, 2020
** CTrue.hpp
** File description:
** ctrue
*/

#pragma once

// Project includes
#include "Factory.hpp"

class nts::CTrue : virtual public nts::Component
{
public:
    CTrue(const std::string & name);
    void dump() const override;
    void computeInput() override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void setInputValue(std::size_t pin, nts::Tristate nb) override;
    nts::Tristate computeOutput() override;
    nts::ComponentType getComponentType() const override;
};
