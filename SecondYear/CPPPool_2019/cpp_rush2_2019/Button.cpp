/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(IConveyorBelt * conveyor)
    : _conveyor { conveyor }
{
}

Button::~Button()
{
}

Wrap * Button::in()
{
    return _conveyor->in();
}

bool Button::out()
{
    return _conveyor->out();
}