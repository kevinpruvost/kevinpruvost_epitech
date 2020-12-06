/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Mixer.hpp"

Mixer::Mixer()
{
    _plugged = true;
    _mixfunc = [](FruitBox & fruitbox) {
        int ret = 0;
        while (fruitbox.nbFruits() > 0) {
            const Fruit *f = fruitbox.pickFruit();
            ret += f->getVitamins();
        }
        return ret;
    };
}
