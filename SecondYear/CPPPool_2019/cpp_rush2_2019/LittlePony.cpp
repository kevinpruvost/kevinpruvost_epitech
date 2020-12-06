/*
** EPITECH PROJECT, 2020
** LittlePony.cpp
** File description:
** LittlePony class code
*/

#include "LittlePony.hpp"

LittlePony::LittlePony(const std::string & title)
    : Toy(title)
{
}

LittlePony::~LittlePony()
{   
}

void LittlePony::isTaken()
{
    std::cout << "yo man" << std::endl;
}
