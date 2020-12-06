/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX01_HPP
#define EX01_HPP

#include <cstring>

template<typename T>
int compare(const T & a, const T & b)
{
    if (a == b)
        return 0;
    if (a < b)
        return -1;
    return 1;
}

#endif // EX01_HPP
