/*
** EPITECH PROJECT, 2020
** Fantasia.cpp
** File description:
** Fantasia
*/

#include "Fantasia.hpp"

#define IType Ingredient::IngredientType

Fantasia::Fantasia(Pizza::PizzaSize size)
    : Pizza(Pizza::PizzaType::Fantasia, size, 4,
    {IType::DOE, IType::TOMATO, IType::EGGPLANT, IType::GOAT_CHEESE, IType::CHIEF_LOVE})
{
}

Fantasia::~Fantasia()
{
}