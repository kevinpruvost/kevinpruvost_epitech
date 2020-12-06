/*
** EPITECH PROJECT, 2020
** Americana.cpp
** File description:
** Americana
*/

#include "Americana.hpp"

#define IType Ingredient::IngredientType

Americana::Americana(Pizza::PizzaSize size)
    : Pizza(Pizza::PizzaType::Americana, size, 2,
        {IType::DOE, IType::GRUYERE, IType::STEAK})
{
}

Americana::~Americana()
{
}