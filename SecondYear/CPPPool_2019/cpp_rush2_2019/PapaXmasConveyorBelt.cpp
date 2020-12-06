/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** PapaXmasConveyorBelt
*/

#include "PapaXmasConveyorBelt.hpp"

PapaXmasConveyorBelt::PapaXmasConveyorBelt()
    : _button (this)
{
}

PapaXmasConveyorBelt::~PapaXmasConveyorBelt()
{
}

Wrap * PapaXmasConveyorBelt::randomGetConveyor()
{
    Wrap * object;
    if (randID)
    {
        object = new GiftPaper;
        randID = false;
    }
    else
    {
        object = new Box;
        randID = true;
    }
    return (Wrap *)object;
}

Wrap * PapaXmasConveyorBelt::in()
{
    if (_object)
        return nullptr;
    // Call for random wrap generation before.
    _object = randomGetConveyor();
    if (_object->isWrap())
    {
        return (Wrap *)_object;
    }
    std::cerr << "There's no wraps on the conveyor belt" << std::endl;
    return nullptr;
}

bool PapaXmasConveyorBelt::out()
{
    if (!_object)
    {
        std::cerr << "There's no object to give to Santa" << std::endl;
        return false;
    }
    _object = nullptr;
    return true;
}

bool PapaXmasConveyorBelt::put(Object * object)
{
    if (_object)
    {
        std::cerr << "There's already an object on the conveyor belt"
                  << std::endl;
        return false;
    }
    if (!object)
    {
        std::cerr << "Object to put does not exist" << std::endl;
        return false;
    }

    _object = object;
    return true;
}

Object * PapaXmasConveyorBelt::take()
{
    if (!_object)
    {
        std::cerr << "There's no object to take" << std::endl;
        return nullptr;
    }

    const auto object = _object;
    _object = nullptr;
    return object;
}

Object * PapaXmasConveyorBelt::get() {
    return this->_object;
}

Button * PapaXmasConveyorBelt::getButton()
{
    return &_button;
}