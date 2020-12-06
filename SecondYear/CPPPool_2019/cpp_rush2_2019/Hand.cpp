/*
** EPITECH PROJECT, 2020
** cpp_rush2_2019
** File description:
** Hand
*/

#include "Hand.hpp"

Hand::Hand(IElf * elf)
    : _elf(elf)
{
}

Hand::~Hand()
{
}

Wrap * Hand::pressIn(Button * button)
{
    if (!button)
    {
        std::cerr << "There's no buttons";
        return nullptr;
    }
    return button->in();
}

bool Hand::pressOut(Button * button) {
    if (button->out())
    {
        std::cout << "Gift sent to Santa !" << std::endl;
        return true;
    }
    return false;
}

Object * Hand::take(size_t index, ITable *table){
    if (_object == nullptr) {
        _object = table->take(index);
        return _object;
    }
    else
    {
        std::cerr << "Elf has already an object in his hands"
                  << std::endl;
        return nullptr;
    }
}

Object * Hand::take(IConveyorBelt *conveyorBelt){
    if (_object == nullptr) {
        _object = conveyorBelt->take();
        return _object;
    }
    else
    {
        std::cerr << "Elf has already an object in his hands"
                  << std::endl;
        return nullptr;
    }
}

bool Hand::put(ITable * table) {
    if (_object != nullptr) {
        if (!table->put(_object))
            return false;
        _object = nullptr;
        return true;
    }
    std::cerr << "There's no object in the elf's hands" << std::endl;
    return false;
}

bool Hand::put(IConveyorBelt * conveyorBelt) {
    if (_object != nullptr) {
        if (!conveyorBelt->put(_object))
            return false;
        _object = nullptr;
        return true;
    }
    std::cerr << "There's no object in the elf's hands" << std::endl;
    return false;
}

bool Hand::objectIsWrap() {
    return _object->isWrap();
}

Object * Hand::getObject() {
    return _object;
}

void Hand::setObject(Object * object) {
    _object = object;
}