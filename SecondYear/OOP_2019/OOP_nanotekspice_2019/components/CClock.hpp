/*
** EPITECH PROJECT, 2020
** CClock.cpp
** File description:
** clock
*/

#pragma once

// Project includes
#include "Factory.hpp"

class nts::CClock : virtual public nts::Component
{
public:
    CClock(const std::string & name);
    void dump() const override;
    nts::Tristate compute(std::size_t pin = 1) override;
    void computeInput() override;
    void refreshClock() override;
    void setInputValue(std::size_t pin, nts::Tristate nb) override;
    nts::Tristate computeOutput() override;
    nts::ComponentType getComponentType() const override;
};
