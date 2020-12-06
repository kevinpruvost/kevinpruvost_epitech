/*
** EPITECH PROJECT, 2020
** Shell.hpp
** File description:
** shell
*/

#pragma once

// Project includes
#include "Manager.hpp"
#include "str_to_array.hpp"
#include "pizza_utils.hpp"

// C++ includes
#include <string>
#include <iostream>
#include <sstream>
#include <regex>
#include <vector>

class Shell
{
public:
    Shell(Manager & manager);
    ~Shell();

    int exec();

private:
    void displayKitchensStatus();

private:
    Manager & _manager;
};