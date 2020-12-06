/*
** EPITECH PROJECT, 2020
** Kitchen.hpp
** File description:
** kitchen
*/

#pragma once

// Project includes
#include "Cook.hpp"
#include "KitchenProcess.hpp"
#include "Stock.hpp"
#include "pizza_utils.hpp"
#include "Thread.hpp"

// C++ includes
#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <map>

#define MAX_PIZZAS 2 * _cooksNumber

std::vector<std::string> split(const std::string & s, char seperator);

class Kitchen
{
public:
	Kitchen(unsigned int cooksNumber, double cookingTimeMultiplier, std::vector<Pizza> & pizzas, bool passive = false);
	Kitchen(unsigned int cooksNumber, double cookingTimeMultiplier, bool passive = false);
	~Kitchen();

	bool addPizzas(const std::vector<std::shared_ptr<Pizza>> & pizzas);
	bool addPizzas(const std::vector<Pizza> & pizzas);
	bool addPizzas(const Pizza & pizza);
	bool addPizzas(const std::shared_ptr<Pizza> & pizza);
	void restock();
	std::vector<std::shared_ptr<Pizza>> & getPizzas();
	const Stock & getStock() const;
	bool isPizzasCookedOrCooking() const;

	void identifyOrder(std::string & order);

	bool isWorking() const;
	int afkTime() const;
	void setAfkTime(int afkTime) { _afkTime = afkTime; }
	void setPizza(const Pizza & pizza) { _pizzas.push_back(std::make_shared<Pizza>(pizza)); }

	void kill();

	void beginAfk();

private:
	int exec();
	bool launchOrder(const std::string & order, const std::vector<std::string> & params);
	bool isChild();
	bool isParent();

	void removeThesePizzas(const std::vector<int> & indexes);

	void sendStatePizzas(const std::vector<Pizza::PizzaState> & states);
	std::vector<Pizza::PizzaState> prepareStatePizzas();
	void sendCookedPizzas(const std::vector<int> & indexes);
	void cookingRepartition();
	void afkTimeRefresh();

	void takeIngredientsInStock(const std::vector<Ingredient::IngredientType> & ing);
	bool readyToDie();

	void checkForCookedPizza();

public:
	bool _markedForAfkManaging;

private:
	bool _dead;

	std::vector<Cook> _cooks;
	std::vector<std::shared_ptr<Pizza>> _pizzas;
	Stock _stock;

	double _cookingTimeMultiplier;
	unsigned int _cooksNumber;

	KitchenProcess _process;

	bool _newCookedPizzas;
	std::chrono::time_point<std::chrono::system_clock> _afkTimeStart;
	int _afkTime;

	std::vector<std::unique_ptr<std::thread>> _threads;
	int _threadsReadyToDie;

	bool usingPizzasParent = false;
	bool _beginAfk = false;

	bool _passive = false;
};