/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef LITTLEHAND_HPP
#define LITTLEHAND_HPP

#include "FruitBox.hpp"

#include "Banana.hpp"
#include "Lime.hpp"
#include "Lemon.hpp"

class LittleHand
{
public:
    static void sortFruitBox(FruitBox & unsorted, FruitBox & lemons,
                             FruitBox & bananas,  FruitBox & limes);
};

#endif // LITTLEHAND_HPP
