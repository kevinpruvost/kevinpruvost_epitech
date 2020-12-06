/*
** EPITECH PROJECT, 2020
** Stock.cpp
** File description:
** stock
*/

#include "Stock.hpp"

// C++ includes
#include <array>

#define IType Ingredient::IngredientType

Stock::Stock()
{
    const std::array<IType, 9> ingredientArray = {
        IType::DOE, IType::TOMATO, IType::GRUYERE, IType::HAM,
        IType::MUSHROOMS, IType::STEAK, IType::EGGPLANT,
        IType::GOAT_CHEESE, IType::CHIEF_LOVE
    };

    for (const auto type : ingredientArray)
        _ingredients.insert({type, 5});
}

Stock::~Stock()
{
}

void Stock::restock()
{
    for (auto & pair : _ingredients)
        ++pair.second;
}

bool Stock::verifyIngredientsInStock(const std::vector<IType> & ingredients)
{
    for (const auto & ingredient : ingredients) {
        if (_ingredients[ingredient] == 0)
            return false;
    }
    return true;
}

bool Stock::takeIngredientsInStock(const std::vector<IType> & ingredients)
{
    if (!verifyIngredientsInStock(ingredients))
        return false;
    for (const auto & ingredient : ingredients)
        --_ingredients[ingredient];
    return true;
}

const std::map<Ingredient::IngredientType, unsigned int> & Stock::getIngredients() const { return _ingredients; }