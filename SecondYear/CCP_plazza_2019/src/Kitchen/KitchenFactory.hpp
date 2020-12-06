/*
** EPITECH PROJECT, 2020
** KitchenFactory.hpp
** File description:
** kitchen factory
*/

#pragma once

// Project includes
#include "Kitchen.hpp"

// C++ includes
#include <memory>

class KitchenFactory
{
public:
    static std::unique_ptr<Kitchen> newKitchen(unsigned int cooksNumber, double cookingTimeMultiplier, std::vector<Pizza> & pizzas);
    static std::unique_ptr<Kitchen> newKitchen(unsigned int cooksNumber, double cookingTimeMultiplier);
};