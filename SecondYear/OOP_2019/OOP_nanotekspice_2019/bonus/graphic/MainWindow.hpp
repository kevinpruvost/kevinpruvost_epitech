/*
** EPITECH PROJECT, 2020
** MainWindow.hpp
** File description:
** main window
*/

#pragma once

// Project includes
#include "Constants.hpp"

#include "GComponent.hpp"

#include "Parser.hpp"
#include "Circuit.hpp"
#include "AddValue.hpp"
#include "Shell.hpp"

// Libs includes
#include <SFML/Graphics.hpp>

// C++ includes
#include <vector>

#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 800.f

class MainWindow
{
public:
    MainWindow(const int ac, const char ** av);
    ~MainWindow();

    int exec();

private:
    void drawCircuit(sf::RenderWindow & window,
        const std::vector<std::unique_ptr<nts::IComponent>> &);

private:
    sf::Event _event;
    int argc;
    const char ** argv;

    std::vector<GComponent> _gcomps;
};