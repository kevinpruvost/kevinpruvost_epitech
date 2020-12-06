/*
** EPITECH PROJECT, 2020
** Regina.hpp
** File description:
** Regina
*/

#pragma once

// Project includes
#include "Pizza.hpp"

class Regina : virtual public Pizza
{
public:
    Regina(Pizza::PizzaSize size);
    ~Regina();
private:
};
