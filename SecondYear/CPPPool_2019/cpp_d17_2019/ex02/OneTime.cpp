/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "OneTime.hpp"

#include <iostream>

OneTime::OneTime(const std::string & key)
    : _key { key }
    , _index { _key.size() }
{

    shiftChange();
}

void OneTime::shiftChange()
{
    ++_index;
    if (_index >= _key.size())
        _index = 0;

    _shift = _key[_index];
    if (_shift < 'A' || _shift > 'z' || (_shift > 'Z' && _shift < 'a'))
    {
        _shift = 0;
        return;
    }

    if (_shift >= 'a' && _shift <= 'z')
        _shift -= 97;

    if (_shift >= 'A' && _shift <= 'Z')
        _shift -= 65;
}

void OneTime::encryptChar(char plainChar)
{
    if (plainChar < 65 || plainChar > 122 || (plainChar > 90 && plainChar < 97))
    {
        std::cout << plainChar << std::flush;
        shiftChange();
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
    shiftChange();
    std::cout << plainChar << std::flush;
}

void OneTime::decryptChar(char plainChar)
{
    if (plainChar < 65 || plainChar > 122 || (plainChar > 90 && plainChar < 97))
    {
        std::cout << plainChar << std::flush;
        shiftChange();
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
    shiftChange();
    std::cout << plainChar << std::flush;
}

void OneTime::reset()
{
    while (_index != 0)
        shiftChange();
}
