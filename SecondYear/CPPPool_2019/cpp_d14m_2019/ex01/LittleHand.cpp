/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "LittleHand.hpp"

#include <iostream>

void LittleHand::sortFruitBox(FruitBox &unsorted, FruitBox &lemons,
                              FruitBox &bananas, FruitBox &limes)
{
    size_t nb = unsorted.nbFruits();

    while (nb > 0)
    {
        const auto fruit = unsorted.pickFruit();
        bool res = true;
        if (dynamic_cast<Lime *>(fruit))
            res = limes.putFruit(fruit);
        else if (dynamic_cast<Banana *>(fruit))
            res = bananas.putFruit(fruit);
        else if (dynamic_cast<Lemon *>(fruit))
            res = lemons.putFruit(fruit);
        else
            unsorted.putFruit(fruit);

        if (!res)
            unsorted.putFruit(fruit);
        --nb;
    }
}
