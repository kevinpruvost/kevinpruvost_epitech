/*
** EPITECH PROJECT, 2020
** MainWindow.cpp
** File description:
** main window
*/

#include "MainWindow.hpp"

MainWindow::MainWindow(SfmlIpc & ipc)
    : _ipc  { ipc }
    , _page { 0   }
{
}

MainWindow::~MainWindow()
{
}

std::vector<Pizza> MainWindow::getPizzas()
{
    auto pizzas = _ipc.getPizzas();
    return _ipc.deserializePizzaVector(pizzas);
}

std::vector<std::unique_ptr<Kitchen>> MainWindow::getKitchens()
{
    auto kitchens = _ipc.getKitchens();
    return _ipc.deserializeKitchenVector(kitchens);
}

void MainWindow::addPizza(const Pizza & pizza)
{
    _ipc.addPizza(pizza);
}

void MainWindow::addPizza(Pizza::PizzaType type, Pizza::PizzaSize size)
{
    addPizza(PizzaFactory::createPizza(type, size));
}

int MainWindow::exec()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    _window.create(videoMode, "Des Freds et des fourchettes.",
    sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

    _window.setFramerateLimit(144);

    std::vector<std::unique_ptr<IPage>> pages;
    pages.emplace_back(new Menu(_window, _event, _ipc));
    pages.emplace_back(new Game(_window, _event, _ipc));
    while (_window.isOpen() && workingProcess)
    {
        if (_window.pollEvent(_event))
        {
            if (_event.type == sf::Event::Closed)
                _window.close();
            pages[_page]->event(_page, workingProcess);
        }
        _window.clear(sf::Color(230, 126, 34));
        if (pages[_page]->exec() == EXIT_FAILURE)
            return EXIT_FAILURE;
        if (pages[_page]->getPageChange() != Page::PageId::NONE)
            _page = pages[_page]->getPageChange();
        _window.display();
    }
    workingProcess = false;
    return EXIT_SUCCESS;
}