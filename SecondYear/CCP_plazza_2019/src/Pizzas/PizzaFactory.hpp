/*
** EPITECH PROJECT, 2020
** PizzaFactory.hpp
** File description:
** pizza factory
*/

#pragma once

// Project includes
#include "Americana.hpp"
#include "Fantasia.hpp"
#include "Margarita.hpp"
#include "Regina.hpp"

// C++ includes
#include <memory>

class PizzaFactory
{
public:
    static std::shared_ptr<Pizza> createSharedPizza(Pizza::PizzaType type, Pizza::PizzaSize size);
    static std::shared_ptr<Pizza> createSharedRandomPizza();
    static Pizza createPizza(Pizza::PizzaType type, Pizza::PizzaSize size);
    static Pizza createRandomPizza();
};