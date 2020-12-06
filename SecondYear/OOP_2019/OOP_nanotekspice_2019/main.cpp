/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

// Project includes
#include "Parser.hpp"
#include "Circuit.hpp"
#include "AddValue.hpp"
#include "Shell.hpp"

// C++ includes
#include <iostream>

int main(int argc, const char ** argv)
{
    if (argc < 2)
        return EXIT_FAILURE;

    nts::Circuit c;
    Parser p(argv[1], c);
    if (!p.parse())
        return EXIT_FAILURE;
    AddValue a(argv, c);
    if (!a.parse())
        return EXIT_FAILURE;
    c.simulate();
    c.display();
    Shell s(c);
    while (s.takeCommand());
    return EXIT_SUCCESS;
}
