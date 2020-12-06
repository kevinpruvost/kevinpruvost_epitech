/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef FRUITNODE_HPP
#define FRUITNODE_HPP

#include "Fruit.hpp"

class FruitNode
{
public:
    FruitNode(Fruit * f, FruitNode * node = nullptr)
        : _fruit { f }
    {
        if (!node)
            return;

        while (node->next != nullptr)
            node = node->next;
        node->next = this;
    }

    ~FruitNode() { }

    int getListSize() const
    {
        auto list = this->next;

        int i = 1;

        while (list != nullptr)
        {
            ++i;
            list = list->next;
        }
        return i;
    }

    FruitNode * getNext() const;

    bool fruitIsAlready(Fruit * f) const
    {
        if (!f)
            return false;

        auto list = this;

        while (list)
        {
            if (list->_fruit == f)
                return true;
            list = list->next;
        }
        return false;
    }

public:
    Fruit * _fruit = nullptr;
    FruitNode * next = nullptr;
};

#endif // FRUITNODE_HPP
