/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** str_to_array
*/

#pragma once

#include <string>

template <class Container>
void splitToArray(const std::string &str, Container &cont, const std::string &delims)
{
    size_t current = 0;
    size_t previous = 0;

    current = str.find_first_of(delims);
    while (current != std::string::npos) {
        cont.push_back(str.substr(previous, current - previous));
        previous = current + 1;
        current = str.find_first_of(delims, previous);
    }
    cont.push_back(str.substr(previous, current - previous));
}