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


FruitBox * const * LittleHand::organizeCoconut(Coconut const * const *coconuts)
{
    int nb = 0;
    while (coconuts[nb] != nullptr)
        ++nb;

    int boxesNb = (nb / 6) + ( ((nb / 6) * 6 != nb) ? 1 : 0);

    FruitBox ** boxes = new FruitBox *[boxesNb+1];

    int x = 0;
    for (int i = 0; i < boxesNb && x < nb; ++i)
    {
        boxes[i] = new FruitBox(6);
        for (int j = 0; j < 6 && x < nb; ++j, ++x)
            boxes[i]->putFruit(const_cast<Coconut *>(coconuts[x]));
    }
    boxes[boxesNb] = nullptr;
    return boxes;
}
