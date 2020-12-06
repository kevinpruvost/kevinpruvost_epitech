/*
** A Kevin Pruvost's project, May 2020
** Page.cpp
** File description:
** page
*/

#include "Page.hpp"

Page::Page(sf::RenderWindow & window, sf::Event & event, SfmlIpc & ipc)
    : _window { window }
    , _event  { event  }
    , _ipc    { ipc }
{
}

Page::~Page()
{
}

void Page::changePage(Page::PageId id)
{
    _pageChange = id;
}

std::vector<std::unique_ptr<Kitchen>> Page::getKitchens()
{
    auto kitchens = _ipc.getKitchens();
    return _ipc.deserializeKitchenVector(kitchens);
}

std::vector<Pizza> Page::getPizzas()
{
    auto pizzas = _ipc.getPizzas();
    return _ipc.deserializePizzaVector(pizzas);
}

void Page::addPizza(const Pizza & pizza)
{
    _ipc.addPizza(pizza);
}

void Page::addPizza(Pizza::PizzaType type, Pizza::PizzaSize size)
{
    addPizza(PizzaFactory::createPizza(type, size));
}

void Page::closeAll()
{
    _ipc.exit();
}