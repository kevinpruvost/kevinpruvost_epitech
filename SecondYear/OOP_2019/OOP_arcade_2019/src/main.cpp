/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

// Project includes
#include "MainWindow.hpp"

// C++ includes
#include <iostream>
#include <random>

int main(const int argc, const char * const * argv)
{
    srand(time(NULL));

    try {
        MainWindow win(argc, argv);
        return win.exec();
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}