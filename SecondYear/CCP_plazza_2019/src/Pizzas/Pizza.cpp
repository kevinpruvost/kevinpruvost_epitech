/*
** EPITECH PROJECT, 2020
** Pizza.cpp
** File description:
** pizza
*/

#include "Pizza.hpp"

// C++ includes
#include <string>

Pizza::Pizza(const PizzaType pizzaType, const PizzaSize pizzaSize,
			 const double cookingTime,
			 const std::vector<Ingredient::IngredientType> & ingredients)
	: _pizzaType   { pizzaType   		 }
	, _pizzaSize   { pizzaSize   		 }
	, _cookingTime { cookingTime 		 }
	, _ingredients { ingredients 		 }
	, _cooked 	   { false		 		 }
	, _cooking	   { false 		 		 }
	, _assigned    { false 		 		 }
	, _state	   { PizzaState::Waiting }
{
	if (pizzaType != PizzaType::Americana
	 && pizzaType != PizzaType::Fantasia
	 && pizzaType != PizzaType::Margarita
	 && pizzaType != PizzaType::Regina) {
		 throw EXCEPTION("Wrong pizza type.");
	 }
	if (pizzaSize != PizzaSize::L
	 && pizzaSize != PizzaSize::M
	 && pizzaSize != PizzaSize::S
	 && pizzaSize != PizzaSize::XL
	 && pizzaSize != PizzaSize::XXL) {
		 throw EXCEPTION("Wrong pizza size.");
	 }
}

Pizza::~Pizza()
{
}

double Pizza::getCookingTime() { return _cookingTime; }

double Pizza::getCookingTime(const double mult) { return _cookingTime * mult; }

std::vector<Ingredient::IngredientType> & Pizza::getIngredients() { return _ingredients; }

bool Pizza::isCooked() const { return _state == PizzaState::Cooked; }

bool Pizza::isCooking() const { return _state == PizzaState::Cooking; }

void Pizza::setCooked() { _state = PizzaState::Cooked; }

void Pizza::setIsCooking() { _state = PizzaState::Cooking; }

Pizza::PizzaType Pizza::getPizzaType() const { return _pizzaType; }

Pizza::PizzaSize Pizza::getPizzaSize() const { return _pizzaSize; }

std::string Pizza::stateString() const
{
	switch (_state)
	{
		case Pizza::PizzaState::Cooked:
			return "Cooked";
			break;
		case Pizza::PizzaState::Cooking:
			return "Cooking";
			break;
		case Pizza::PizzaState::Assigned:
			return "Assigned";
			break;
		default:
			return "Waiting";
			break;
	}
}

void Pizza::setAssigned() { _state = PizzaState::Assigned; }

bool Pizza::isAssigned() const { return _state == PizzaState::Assigned || _state == PizzaState::Cooking || _state == PizzaState::Cooked; }

const Pizza::PizzaState & Pizza::getState() const { return _state; }

void Pizza::setState(Pizza::PizzaState state) { _state = state; }