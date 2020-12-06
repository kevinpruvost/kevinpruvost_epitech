/*
** EPITECH PROJECT, 2020
** Regina.cpp
** File description:
** Regina
*/

#include "Regina.hpp"

#define IType Ingredient::IngredientType

Regina::Regina(Pizza::PizzaSize size)
    : Pizza(Pizza::PizzaType::Regina, size, 2,
    {IType::DOE, IType::TOMATO, IType::GRUYERE, IType::HAM, IType::MUSHROOMS})
{
}

Regina::~Regina()
{
}