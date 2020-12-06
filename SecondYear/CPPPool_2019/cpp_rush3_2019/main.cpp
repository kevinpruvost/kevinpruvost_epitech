/*
** EPITECH PROJECT, 2020
** main.cpp
** File description:
** main
*/

#include "MainWindow.hpp"
#include "display/NCurses.hpp"

int main(int ac, char **av)
{
    Htop core;
    int value = core.parssing(ac, av);

    if (value == EXIT_FAILURE)
        return EXIT_FAILURE;
    core.chargeModule();

    if (core.getBool(Htop::enum_module::TEXT))
    {
        NCurses ncurse(core);
        return EXIT_SUCCESS;
    }

    if (core.getBool(Htop::enum_module::GRAPHICS))
    {
        QApplication app(ac, av);
        MainWindow mainWindow(core);
        return app.exec();
    }

    return EXIT_FAILURE;
}
