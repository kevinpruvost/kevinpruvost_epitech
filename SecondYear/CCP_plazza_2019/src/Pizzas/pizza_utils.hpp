/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** pizza_utils
*/

#pragma once

// Project includes
#include "Pizza.hpp"
#include "PizzaFactory.hpp"
#include "str_to_array.hpp"

// C++ includes
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>

const std::map<std::string, Pizza::PizzaType> pizz_types_str_to_enum = {
    {"regina", Pizza::Regina}, {"margarita", Pizza::Margarita},
    {"americana", Pizza::Americana}, {"fantasia", Pizza::Fantasia}
};

const std::map<std::string, Pizza::PizzaSize> pizz_sizes_str_to_enum = {
    {"S", Pizza::S}, {"M", Pizza::M}, {"L", Pizza::L}, {"XL", Pizza::XL},
    {"XXL", Pizza::XXL}
};

const std::map<Pizza::PizzaType, std::string> pizz_types_enum_to_str = {
    {Pizza::Regina, "regina"}, {Pizza::Margarita, "margarita"},
    {Pizza::Americana, "americana"}, {Pizza::Fantasia, "fantasia"}
};

const std::map<Pizza::PizzaSize, std::string> pizz_sizes_enum_to_str = {
    {Pizza::S, "S"}, {Pizza::M, "M"}, {Pizza::L, "L"}, {Pizza::XL, "XL"},
    {Pizza::XXL, "XXL"}
};

const std::map<Ingredient::IngredientType, std::string> ingred_enum_to_str = {
    {Ingredient::DOE, "Doe"}, {Ingredient::TOMATO, "Tomato"},
    {Ingredient::GRUYERE, "Gruyere"}, {Ingredient::HAM, "Ham"},
    {Ingredient::MUSHROOMS, "Mushrooms"}, {Ingredient::STEAK, "Steak"},
    {Ingredient::EGGPLANT, "Eggplant"}, {Ingredient::GOAT_CHEESE, "Goat cheese"},
    {Ingredient::CHIEF_LOVE, "Chief love"}
};

const std::map<std::string, Ingredient::IngredientType> ingred_str_to_enum = {
    {"Doe", Ingredient::DOE}, {"Tomato", Ingredient::TOMATO},
    {"Gruyere", Ingredient::GRUYERE}, {"Ham", Ingredient::HAM},
    {"Mushrooms", Ingredient::MUSHROOMS}, {"Steak", Ingredient::STEAK},
    {"Eggplant", Ingredient::EGGPLANT}, {"Goat cheese", Ingredient::GOAT_CHEESE},
    {"Chief love", Ingredient::CHIEF_LOVE}
};

const std::map<Pizza::PizzaState, std::string> states_to_str = {
    {Pizza::PizzaState::Waiting,  "Waiting"},
    {Pizza::PizzaState::Assigned, "Assigned"},
    {Pizza::PizzaState::Cooked,   "Cooked"},
    {Pizza::PizzaState::Cooking,  "Cooking"}
};

const std::map<std::string, Pizza::PizzaState> str_to_states = {
    {"Waiting",  Pizza::PizzaState::Waiting},
    {"Assigned", Pizza::PizzaState::Assigned},
    {"Cooked",   Pizza::PizzaState::Cooked},
    {"Cooking",  Pizza::PizzaState::Cooking}
};

std::vector<Pizza> CreatePizzasFromSring(std::string str);
Pizza CreatePizzaFromSring(std::string str);

std::string CreateStringFromPizzas(std::vector<Pizza> pizzas);
std::string CreateStringFromPizzas(Pizza pizza);
std::string CreateStringFromPizzas(const std::vector<std::shared_ptr<Pizza>> & pizzas);

std::string CreateStringFromIngredients(const std::vector<Ingredient::IngredientType> & ings);
std::string CreateStringFromIngredients(const Ingredient::IngredientType ing);

std::vector<Ingredient::IngredientType> CreateIngredientsFromString(const std::string & str);
Ingredient::IngredientType CreateIngredientFromString(const std::string & str);

std::vector<int> CreateIntsFromString(std::string str);

bool isPizzaTypeValid(std::string str);
bool isPizzaTypeValid(Pizza::PizzaType pizza);

std::vector<Pizza::PizzaState> CreateStatesFromString(const std::string & str);
std::string CreateStringFromStates(const std::vector<Pizza::PizzaState> & states);