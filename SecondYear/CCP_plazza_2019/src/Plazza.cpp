/*
** EPITECH PROJECT, 2020
** Plazza.cpp
** File description:
** plazza
*/

#include "Plazza.hpp"

// C++ includes
#include <string>
#include <thread>
#include <chrono>

// C includes
#include <unistd.h>

Plazza::Plazza(const char ** argv)
try	: _cookingTimeMultiplier  { std::stod(argv[1]) }
	, _cooksPerKitchen		  { std::stoi(argv[2]) }
	, _replaceTimeIngredients { std::stoi(argv[3]) }
	, manager { _cookingTimeMultiplier, _cooksPerKitchen, _replaceTimeIngredients }
	, shell   { manager }
{
}
catch (const std::exception & e)
{
	throw EXCEPTION("Error at plazza creation : " + e.what());
}

Plazza::~Plazza()
{
}

int Plazza::exec()
{
	std::unique_ptr<std::thread> t1(new std::thread(&Manager::exec, std::ref(manager)));
	t1->detach();
	if (isChildProcess)
		return EXIT_SUCCESS;

	return shell.exec();
}

void Plazza::closePlazza()
{
	workingProcess = false;
	kill(getpid(), SIGINT);
}

const std::vector<std::shared_ptr<Kitchen>> & Plazza::getKitchens() const
{
    return manager.getKitchens();
}

const std::vector<std::shared_ptr<Pizza>> & Plazza::getPizzas() const
{
    return manager.getPizzas();
}