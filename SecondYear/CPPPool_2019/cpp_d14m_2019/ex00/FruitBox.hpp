/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef FRUITBOX_HPP
#define FRUITBOX_HPP

#include "FruitNode.hpp"

class FruitBox
{
public:
    FruitBox(int size);

    int nbFruits() const;
    bool putFruit(Fruit * f);
    Fruit * pickFruit();
    FruitNode * head() const;

private:
    int _size;
    FruitNode * _list = nullptr;
};

#endif // FRUITBOX_HPP
