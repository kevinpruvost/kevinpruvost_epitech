/*
** EPITECH PROJECT, 2020
** KitchenFactory.cpp
** File description:
** kitchen
*/

#include "KitchenFactory.hpp"

std::unique_ptr<Kitchen> KitchenFactory::newKitchen(unsigned int cooksNumber, double cookingTimeMultiplier, std::vector<Pizza> & pizzas)
{
    return std::make_unique<Kitchen>(cooksNumber, cookingTimeMultiplier, pizzas);
}

std::unique_ptr<Kitchen> KitchenFactory::newKitchen(unsigned int cooksNumber, double cookingTimeMultiplier)
{
    return std::make_unique<Kitchen>(cooksNumber, cookingTimeMultiplier);
}