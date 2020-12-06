/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX02_HPP
#define EX02_HPP

#include <iostream>

template<typename T>
void print(const T & part)
{
    std::cout << part << std::endl;
}

template<typename T>
void foreach(T * tab, void (* func)(const T &), int size)
{
    for (int i = 0; i < size; ++i)
    {
        func(tab[i]);
    }
}

#endif // EX02_HPP
