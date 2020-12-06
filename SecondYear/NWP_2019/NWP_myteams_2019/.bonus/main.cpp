/*
** A Kevin Pruvost's project, May 2020
** main.cpp
** File description:
** main
*/

#include "MainWindow.hpp"

int main(int ac, char ** av)
{
    MainWindow mw(ac, av);

    return mw.exec();
}