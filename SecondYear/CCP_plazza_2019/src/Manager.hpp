/*
** EPITECH PROJECT, 2020
** Manager.hpp
** File description:
** manager
*/

#pragma once

// C++ includes
#include <string>
#include <vector>
#include <chrono>

// Project includes
#include "KitchenFactory.hpp"
#include "Exception.hpp"
#include "PizzaFactory.hpp"

#define NBR_PIZZA_PER_COOK  2
#define INACTIVE_TIME   5000

class Manager
{
public:
    Manager(double cookingTimeMultiplier, int cooksPerKitchen, int replaceTimeIngredients);
    ~Manager();

    int exec();
    std::vector<std::shared_ptr<Kitchen>> & getStatus();
    void createNewPizza(Pizza::PizzaType Type, Pizza::PizzaSize size, int number);
    void createNewKitchens();
    void resetStock();
    std::vector<int> findLazyKitchen(int size);
    void inactif();

    void getInactif(std::shared_ptr<Kitchen> & kitchen, int index);

    const std::vector<std::shared_ptr<Kitchen>> & getKitchens() const;
    const std::vector<std::shared_ptr<Pizza>> & getPizzas() const;

private:
	std::vector<std::shared_ptr<Kitchen>> _kitchens;
	double _cookingTimeMultiplier;
	int _cooksPerKitchen;
	int _replaceTimeIngredients;
    std::vector<std::shared_ptr<Pizza>> _newPizza;
    std::vector<std::shared_ptr<Pizza>> _pizzaMemory;
};
