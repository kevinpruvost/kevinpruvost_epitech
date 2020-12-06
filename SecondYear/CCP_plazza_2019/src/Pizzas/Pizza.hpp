/*
** EPITECH PROJECT, 2020
** Pizza.hpp
** File description:
** pizza
*/

#pragma once

// Project includes
#include "Exception.hpp"
#include "Ingredient.hpp"

// C++ includes
#include <vector>

class Pizza
{
public:
	enum PizzaType
	{
		Regina = 1,
		Margarita = 2,
		Americana = 4,
		Fantasia = 8
	};
	enum PizzaSize
	{
		S = 1,
		M = 2,
		L = 4,
		XL = 8,
		XXL = 16
	};
	enum PizzaState
	{
		Waiting,
		Assigned,
		Cooking,
		Cooked
	};

	Pizza(const PizzaType pizzaType, const PizzaSize pizzaSize,
		  const double cookingTime,
		  const std::vector<Ingredient::IngredientType> & ingredients);
	~Pizza();

	double getCookingTime();
	double getCookingTime(const double mult);
	std::vector<Ingredient::IngredientType> & getIngredients();

	bool isCooked() const;
	bool isCooking() const;
	bool isAssigned() const;
	void setCooked();
	void setIsCooking();
	void setAssigned();

	const PizzaState & getState() const;
	void setState(Pizza::PizzaState);

	std::string stateString() const;

	PizzaType getPizzaType() const;
	PizzaSize getPizzaSize() const;

private:
	PizzaType _pizzaType;
	PizzaSize _pizzaSize;

	double _cookingTime;
	std::vector<Ingredient::IngredientType> _ingredients;

	bool _cooked;
	bool _cooking;
	bool _assigned;

	PizzaState _state;
};