/*
** EPITECH PROJECT, 2020
** MainWindow.hpp
** File description:
** main window
*/

#pragma once

// Project includes
#include "Plazza.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "SfmlIpc.hpp"

// Sfml includes
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class MainWindow
{
public:
    MainWindow(SfmlIpc & ipc);
    ~MainWindow();
    std::vector<Pizza> getPizzas();
    std::vector<std::unique_ptr<Kitchen>> getKitchens();
    void addPizza(const Pizza & pizza);
    void addPizza(Pizza::PizzaType type, Pizza::PizzaSize size);

    int exec();

private:
    std::unique_ptr<sf::Thread> _fred;

    // Pour s'assurer qu'il soit seul dans son thread.
public:
    sf::RenderWindow _window;

    sf::Event _event;

    SfmlIpc & _ipc;

    int _page;
};