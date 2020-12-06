/*
** EPITECH PROJECT, 2020
** Box.cpp
** File description:
** Box class declaration
*/

//C++ includes
#include "Box.hpp"

Box::Box()
    : Wrap("Box")
{
}

Box::~Box()
{
}

Wrap * Box::wrapMeThat(Object * object)
{
    if (!object)
    {
        std::cerr << "Object in parameter doesn't exist" << std::endl;
        return nullptr;
    }
    if (!_opened)
    {
        std::cerr << "Box is closed" << std::endl;
        return nullptr;
    }
    return containObject(object);
}