/*
** EPITECH PROJECT, 2020
** Warrior.cpp
** File description:
** ex00
*/

#include "Teddy.hpp"

Teddy::Teddy(const std::string & title)
    : Toy(title)
    
{

}

Teddy::~Teddy() {

}

void Teddy::isTaken()
{
    std::cout << "gra hu" << std::endl;
}