/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "FruitBox.hpp"

#include <iostream>

FruitBox::FruitBox(int size)
    : _size { size }
{
}

int FruitBox::nbFruits() const
{
    if (!_list)
        return 0;
    return _list->getListSize();
}

bool FruitBox::putFruit(Fruit * f)
{
    if (_list)
    {
        if (_size <= _list->getListSize() || _list->fruitIsAlready(f))
            return false;
    }
    const auto node = new FruitNode(f, _list);
    if (!_list)
        _list = node;
    return true;
}

Fruit * FruitBox::pickFruit()
{
    if (!_list)
        return nullptr;

    auto listFruit = _list;
    auto fruit = _list->_fruit;
    _list->_fruit = nullptr;
    _list = _list->next;
    delete listFruit;
    return fruit;
}

FruitNode * FruitBox::head() const
{
    return _list;
}
