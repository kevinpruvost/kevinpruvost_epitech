/*
** EPITECH PROJECT, 2020
** Wrap.cpp
** File description:
** Wrap class declaration
*/

#include "Wrap.hpp"

Wrap::Wrap(const std::string & name)
    : Object(name)
{

}

bool Wrap::isOpen() const
{
    return _opened;
}

Wrap * Wrap::containObject(Object *object)
{
    if (!object)
    {
        std::cerr << "Object in parameter doesn't exist" << std::endl;
        return nullptr;
    }
    if (_objectContained)
    {
        std::cerr << "There is already something in "
                  << _objectContained->getName() << std::endl; 
        return nullptr;
    }
    _objectContained = object;
    std::cout << "tuuuut tuuut tuut" << std::endl;
    closeMe();
    return this;
}

Wrap & Wrap::operator<<(Object * object)
{
    wrapMeThat(object);
    return *this;
}

Object * Wrap::getContainedObject() const
{
    return _objectContained;
}

void Wrap::openMe()
{
    _opened = true;
}

void Wrap::closeMe()
{
    _opened = false;
}

Object * Wrap::takeContainedObject()
{
    if (!_opened)
    {
        std::cerr << "Wrap is closed, you can't take the object." << std::endl;
        return nullptr;
    }

    const auto object = _objectContained;
    _objectContained = nullptr;
    return object;
}

void Wrap::isTaken()
{
    std::cout << "whistles while working\n";
}

std::ostream & operator<<(std::ostream & os, Wrap * wrap)
{
    if (wrap->getContainedObject())
    {
        os << wrap->getName() << " contains a "
        << wrap->getContainedObject()->getName() << std::endl;
        if (wrap->getContainedObject()->isWrap())
        {
            operator<<(os, (Wrap *)(wrap->getContainedObject()));
        }
        return os;
    }
    os << wrap->getName() << " does not contain an object\n";
    return os;
}