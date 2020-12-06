/*
** EPITECH PROJECT, 2020
** Stock.hpp
** File description:
** stock
*/

#pragma once

// Project includes
#include "Ingredient.hpp"

// C++ includes
#include <map>
#include <vector>

class Stock
{
public:
    Stock();
    ~Stock();

    void restock();
    bool takeIngredientsInStock(const std::vector<Ingredient::IngredientType> & ingredients);
    const std::map<Ingredient::IngredientType, unsigned int> & getIngredients() const;
    bool verifyIngredientsInStock(const std::vector<Ingredient::IngredientType> & ingredients);

private:
    std::map<Ingredient::IngredientType, unsigned int> _ingredients;
};