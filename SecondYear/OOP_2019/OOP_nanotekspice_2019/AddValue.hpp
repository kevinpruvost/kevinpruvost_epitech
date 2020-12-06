/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** AddValue
*/

#ifndef ADDVALUE_HPP_
#define ADDVALUE_HPP_

#include "Circuit.hpp"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

class AddValue
{
public:
    AddValue(const char * const * av, nts::Circuit & circuit);
    ~AddValue();

    bool parse();
    bool exec();

private:
    nts::Circuit & _circuit;
    const char * const * av;
};

#endif /* !ADDVALUE_HPP_ */
