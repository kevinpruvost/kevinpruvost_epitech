/*
** EPITECH PROJECT, 2020
** Cook.hpp
** File description:
** plazza
*/

#pragma once

// Project includes
#include "PizzaFactory.hpp"

// C++ includes
#include <list>
#include <functional>
#include <chrono>
#include <thread>
#include <condition_variable>

class Cook
{
public:
	Cook(const double);
	~Cook();

	double getRemainingCookingTotalTime();
	bool cookPizza(Pizza & pizza);
	bool pizzaNewlyCooked();
	bool isCooking();
	bool isFull() const;
	bool isEmpty() const;

public:
	void cooking(double & times);

private:
	void cookThread();
	double getFullTime();
	int SecondToMillisecond(double);
	void addPizzaToThread(Pizza & pizza);

private:
	std::list<std::reference_wrapper<Pizza>> _pizzas;

	double time = 0;
	bool _pizzaNewlyCooked;
	bool _isCooking;
	const double _cookingTimeMultiplier;
};