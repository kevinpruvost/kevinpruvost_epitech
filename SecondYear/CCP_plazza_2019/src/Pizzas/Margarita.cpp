/*
** EPITECH PROJECT, 2020
** Margarita.cpp
** File description:
** margarita
*/

#include "Margarita.hpp"

#define IType Ingredient::IngredientType

Margarita::Margarita(Pizza::PizzaSize size)
    : Pizza(Pizza::PizzaType::Margarita, size, 1,
    {IType::DOE, IType::TOMATO, IType::GRUYERE})
{
}

Margarita::~Margarita()
{
}