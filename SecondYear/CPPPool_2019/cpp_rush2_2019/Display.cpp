/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Hand
*/

#include "Display.hpp"

#include <iostream>

std::ostream & operator<<(std::ostream & os,
                             std::vector<std::string> titles)
{
    auto ite = titles.begin();
    for (; ite != titles.end();)
    {
        os << *ite;
        ++ite;
        if (ite != titles.end())
            os << ", ";
    }
    os << std::endl;
    return os;
}