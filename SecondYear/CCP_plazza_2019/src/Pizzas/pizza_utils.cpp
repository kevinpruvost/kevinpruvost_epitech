/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** pizza_utils
*/

#include "pizza_utils.hpp"

std::vector<Pizza> CreatePizzasFromSring(std::string str)
{
    std::vector<Pizza> pizzas;
    std::vector<std::string> pizza_strings;
    std::vector<std::string> pizza;

    splitToArray(str, pizza_strings, ";");
    for (std::string & pizza_str : pizza_strings) {
        pizza.clear();
        splitToArray(pizza_str, pizza, " ");
        if (pizza.size() != 2)
            throw EXCEPTION("Cannot create pizza from string: invalid string");
        pizzas.push_back(PizzaFactory::createPizza(pizz_types_str_to_enum.at(pizza.at(0)), pizz_sizes_str_to_enum.at(pizza.at(1))));
    }
    return (pizzas);
}

Pizza CreatePizzaFromSring(std::string str)
{
    std::vector<std::string> pizza;

    splitToArray(str, pizza, " ");
    if (pizza.size() != 2)
        throw EXCEPTION("Cannot create pizza from string: invalid string");
    return (PizzaFactory::createPizza(pizz_types_str_to_enum.at(pizza.at(0)), pizz_sizes_str_to_enum.at(pizza.at(1))));
}

std::string CreateStringFromPizzas(std::vector<Pizza> pizzas)
{
    std::string output = "";
    size_t i = 0;

    for (const auto & pizza : pizzas) {
        if (i != 0)
            output += ";";
        output += pizz_types_enum_to_str.at(pizza.getPizzaType()) + " " + pizz_sizes_enum_to_str.at(pizza.getPizzaSize());
        ++i;
    }
    return (output);
}

std::string CreateStringFromPizzas(const std::vector<std::shared_ptr<Pizza>> & pizzas)
{
    std::string output = "";
    size_t i = 0;

    for (const auto & pizza : pizzas) {
        if (i != 0)
            output += ";";
        output += pizz_types_enum_to_str.at(pizza->getPizzaType()) + " " + pizz_sizes_enum_to_str.at(pizza->getPizzaSize());
        ++i;
    }
    return (output);
}

std::string CreateStringFromPizzas(Pizza pizza)
{
    return (pizz_types_enum_to_str.at(pizza.getPizzaType()) + " " + pizz_sizes_enum_to_str.at(pizza.getPizzaSize()));
}

std::vector<int> CreateIntsFromString(std::string str)
{
    std::vector<int> ints;
    std::vector<std::string> int_strings;
    std::vector<std::string> pizza;

    splitToArray(str, int_strings, ";");
    for (std::string & pizza_str : int_strings)
        ints.push_back(std::stoi(pizza_str));
    return (ints);
}

bool isPizzaTypeValid(std::string str)
{
    for (auto pizz : pizz_types_str_to_enum)
        if (pizz.first == str)
            return (true);
    return (false);
}

bool isPizzaTypeValid(Pizza::PizzaType pizza)
{
    for (auto pizz : pizz_types_str_to_enum)
        if (pizz.second == pizza)
            return (true);
    return (false);
}

std::string CreateStringFromIngredients(const std::vector<Ingredient::IngredientType> & ings)
{
    std::string output = "";
    size_t i = 0;

    for (Ingredient::IngredientType ingredient : ings) {
        if (i != 0)
            output += ";";
        output += ingred_enum_to_str.at(ingredient);
        ++i;
    }
    return (output);
}

std::string CreateStringFromIngredients(const Ingredient::IngredientType ing)
{
    return ingred_enum_to_str.at(ing);
}

std::vector<Ingredient::IngredientType> CreateIngredientsFromString(const std::string & str)
{
    std::vector<Ingredient::IngredientType> ingredients;
    std::vector<std::string> ingredients_strings;


    splitToArray(str, ingredients_strings, ";");
    for (std::string & ingredient : ingredients_strings)
        ingredients.push_back(ingred_str_to_enum.at(ingredient));

    return (ingredients);
}

Ingredient::IngredientType CreateIngredientFromString(const std::string & str)
{
    return (ingred_str_to_enum.at(str));
}

std::vector<Pizza::PizzaState> CreateStatesFromString(const std::string & str)
{
    std::vector<Pizza::PizzaState> states;
    std::vector<std::string> states_strings;

    splitToArray(str, states_strings, ";");
    for (auto & state : states_strings)
    {
        states.push_back(str_to_states.at(state));
    }
    return states;
}

std::string CreateStringFromStates(const std::vector<Pizza::PizzaState> & states)
{
    std::string str;

    for (auto it = states.begin(); it != states.end(); ++it)
    {
        str += states_to_str.at(*it);
        if (it + 1 != states.end())
            str += ";";
    }
    return str;
}