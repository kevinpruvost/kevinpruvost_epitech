/*
** EPITECH PROJECT, 2020
** PizzaFactory.cpp
** File description:
** pizza factory
*/

#include "PizzaFactory.hpp"

std::shared_ptr<Pizza> PizzaFactory::createSharedPizza(Pizza::PizzaType type, Pizza::PizzaSize size)
{
    if (type == Pizza::PizzaType::Americana)
        return std::make_shared<Pizza>(Americana(size));
    if (type == Pizza::PizzaType::Fantasia)
        return std::make_shared<Pizza>(Fantasia(size));
    if (type == Pizza::PizzaType::Regina)
        return std::make_shared<Pizza>(Regina(size));
    if (type == Pizza::PizzaType::Margarita)
        return std::make_shared<Pizza>(Margarita(size));
    throw EXCEPTION("Wrong Pizza type.");
    return std::make_shared<Pizza>(Americana(size));
}

Pizza PizzaFactory::createPizza(Pizza::PizzaType type, Pizza::PizzaSize size)
{
    if (type == Pizza::PizzaType::Americana)
        return Americana(size);
    if (type == Pizza::PizzaType::Fantasia)
        return Fantasia(size);
    if (type == Pizza::PizzaType::Regina)
        return Regina(size);
    if (type == Pizza::PizzaType::Margarita)
        return Margarita(size);
    throw EXCEPTION("Wrong Pizza type.");
    return Americana(size);
}

std::shared_ptr<Pizza> PizzaFactory::createSharedRandomPizza()
{
    static bool randed = false;
    if (!randed)
    {
        srand(time(NULL));
        randed = true;
    }

    static const std::vector<Pizza::PizzaType> types = {
        Pizza::PizzaType::Americana,
        Pizza::PizzaType::Fantasia,
        Pizza::PizzaType::Margarita,
        Pizza::PizzaType::Regina
    };

    static const std::vector<Pizza::PizzaSize> sizes = {
        Pizza::PizzaSize::L,
        Pizza::PizzaSize::M,
        Pizza::PizzaSize::S,
        Pizza::PizzaSize::XL,
        Pizza::PizzaSize::XXL
    };

    return createSharedPizza(types[rand() % types.size()], sizes[rand() % sizes.size()]);
}

Pizza PizzaFactory::createRandomPizza()
{
    static bool randed = false;
    if (!randed)
    {
        srand(time(NULL));
        randed = true;
    }

    static const std::vector<Pizza::PizzaType> types = {
        Pizza::PizzaType::Americana,
        Pizza::PizzaType::Fantasia,
        Pizza::PizzaType::Margarita,
        Pizza::PizzaType::Regina
    };

    static const std::vector<Pizza::PizzaSize> sizes = {
        Pizza::PizzaSize::L,
        Pizza::PizzaSize::M,
        Pizza::PizzaSize::S,
        Pizza::PizzaSize::XL,
        Pizza::PizzaSize::XXL
    };

    return createPizza(types[rand() % types.size()], sizes[rand() % sizes.size()]);
}