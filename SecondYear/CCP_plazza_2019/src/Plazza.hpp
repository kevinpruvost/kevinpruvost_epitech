/*
** EPITECH PROJECT, 2020
** Plazza.hpp
** File description:
** plazza
*/

#pragma once

// Project includes
#include "Manager.hpp"
#include "Shell.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

class Plazza
{
public:
	Plazza(const char ** argv);
	~Plazza();

	int exec();
	void closePlazza();

    const std::vector<std::shared_ptr<Kitchen>> & getKitchens() const;
    const std::vector<std::shared_ptr<Pizza>> & getPizzas() const;

private:
	double _cookingTimeMultiplier;
	int _cooksPerKitchen;
	int _replaceTimeIngredients;

public:
	Manager manager;
	Shell shell;
};