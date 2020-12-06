/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Cesar.hpp"

#include <iostream>

Cesar::Cesar()
{

}

void Cesar::encryptChar(char plainChar)
{
    if (plainChar < 65 || plainChar > 122 || (plainChar > 90 && plainChar < 97))
    {
        std::cout << plainChar << std::flush;
        ++_shift;
        return;
    }

    int limits[2] = {'A', 'Z'};
    if (plainChar >= 'a' && plainChar <= 'z')
    {
        limits[0] = 'a';
        limits[1] = 'z';
    }

    for (int i = 0; i < _shift; ++i)
    {
        ++plainChar;
        if (plainChar > limits[1])
            plainChar = limits[0];
    }
    ++_shift;
    std::cout << plainChar << std::flush;
}

void Cesar::decryptChar(char plainChar)
{
    if (plainChar < 65 || plainChar > 122 || (plainChar > 90 && plainChar < 97))
    {
        std::cout << plainChar << std::flush;
        ++_shift;
        return;
    }

    int limits[2] = {'A', 'Z'};
    if (plainChar >= 'a' && plainChar <= 'z')
    {
        limits[0] = 'a';
        limits[1] = 'z';
    }

    for (int i = 0; i <_shift; ++i)
    {
        --plainChar;
        if (plainChar < limits[0])
            plainChar = limits[1];
    }
    ++_shift;
    std::cout << plainChar << std::flush;
}

void Cesar::reset()
{
    _shift = 3;
}
