/*
** EPITECH PROJECT, 2020
** Object.cpp
** File description:
** Object class code
*/

#include "Object.hpp"

Object::Object(const std::string & name)
    : _name { name }
{

}

Object::~Object()
{
}

std::string Object::getName(void)
{
    return (_name);
}

void Object::setName(const std::string & name)
{
    _name = name;
}

bool Object::isWrap()
{
    if (_name == "Wrap" || _name == "GiftPaper" || _name == "Box")
        return true;
    return false;
}