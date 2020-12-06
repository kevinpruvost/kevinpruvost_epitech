/*
** EPITECH PROJECT, 2020
** Cook.cpp
** File description:
** plazza
*/

#include "Cook.hpp"

// Project includes
#include "pizza_utils.hpp"
#include "Thread.hpp"

// C++ includes
#include <string>
#include <thread>
#include <algorithm>
#include <chrono>
#include <cstdlib>

// C includes
#include <unistd.h>

Cook::Cook(const double cookingTimeMultiplier)
    : _pizzaNewlyCooked { false }
    , _isCooking { false }
    , _cookingTimeMultiplier { cookingTimeMultiplier }
{
    _pizzas.clear();
}

Cook::~Cook()
{
}

double Cook::getFullTime()
{
    double time = 0;

    for (auto & k : _pizzas) {
        time += k.get().getCookingTime(_cookingTimeMultiplier);
    }

    return time;
}

int Cook::SecondToMillisecond(double seconds)
{
    return seconds / 1000;
}

void Cook::cooking(double & times)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    time -= 0.1;
    times -= 0.1;
}

void Cook::cookThread()
{
    Pizza & pizza = _pizzas.front();
    double times = pizza.getCookingTime(_cookingTimeMultiplier);
    time = getFullTime();

    pizza.setIsCooking();

    std::unique_ptr<std::thread> cooking(new std::thread([times, this]{
        double timesThread = times;

        while (timesThread > 0)
            this->cooking(timesThread);
    }));

    DEBUG("Time to cook : " << times * 1000 << "ms.")

    std::this_thread::sleep_for(std::chrono::milliseconds((int)(times * 1000)));

    pizza.setCooked();

    DEBUG_FLUSH(CreateStringFromPizzas(pizza) << " ")
    DEBUG("Cooked")

    _pizzaNewlyCooked = true;

    _pizzas.pop_front();
    cooking->join();
    if (_pizzas.size() > 0) {
        cookThread();
    }
    _isCooking = false;
}

double Cook::getRemainingCookingTotalTime() // return temps de travail actuel
{
    if (time < 0)
        time = 0;
    return time;
}

bool Cook::cookPizza(Pizza & pizza)
{
    if (pizza.isAssigned())
        return false;
    if (_pizzas.size() == 0 || _pizzas.size() == 1 ) {
        _pizzas.push_back(pizza);
        pizza.setAssigned();
        if (!_isCooking) {
            _isCooking = true;
            std::thread obj(&Cook::cookThread, this);
            obj.detach();
        }
        return true;
    }
    return false;
}

bool Cook::pizzaNewlyCooked()
{
    if (_pizzaNewlyCooked) {
        _pizzaNewlyCooked = false;
        return true;
    }
    return false;
}

bool Cook::isFull() const
{
    return _pizzas.size() >= 2;
}

bool Cook::isEmpty() const
{
    return _pizzas.size() == 0;
}

bool Cook::isCooking()
{
    return _isCooking;
}