/*
** EPITECH PROJECT, 2020
** IDisplayModule.hpp
** File description:
** display module interface
*/

#pragma once

// C++ includes
#include <string>

class IDisplayModule
{
public:
    virtual ~IDisplayModule() = default;

    virtual void updateEvent() = 0;
    virtual void setTexture(const std::string & fileName) = 0;
    virtual void display() = 0;
};