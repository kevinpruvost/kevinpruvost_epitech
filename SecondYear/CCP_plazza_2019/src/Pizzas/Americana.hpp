/*
** EPITECH PROJECT, 2020
** Americana.hpp
** File description:
** Americana
*/

#pragma once

// Project includes
#include "Pizza.hpp"

class Americana : virtual public Pizza
{
public:
    Americana(Pizza::PizzaSize size);
    ~Americana();

private:
};
