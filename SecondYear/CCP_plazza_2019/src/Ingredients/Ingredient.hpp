/*
** EPITECH PROJECT, 2020
** Ingredient.hpp
** File description:
** ingredient
*/

#pragma once

class Ingredient
{
public:
    enum IngredientType
    {
        DOE, TOMATO, GRUYERE, HAM, MUSHROOMS, STEAK,
        EGGPLANT, GOAT_CHEESE, CHIEF_LOVE
    };

    Ingredient(IngredientType type);
    ~Ingredient();

private:
    IngredientType _type;
};
