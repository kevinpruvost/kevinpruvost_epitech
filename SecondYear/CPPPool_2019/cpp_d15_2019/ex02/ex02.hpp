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
T min(const T & a, const T & b)
{
    std::cout << "template min" << std::endl;
    if (a < b)
        return a;
    return b;
}

int min(const int & a, const int & b)
{
    std::cout << "non-template min" << std::endl;
    if (a < b)
        return a;
    return b;
}

template<typename T>
T templateMin(const T * a, const int b)
{
    T ret = a[0];
    for (int i = 0; i + 1 < b; ++i)
        ret = min<T>(ret, a[i+1]);
    return ret;
}

int nonTemplateMin(const int * a, const int b)
{
    int ret = a[0];
    for (int i = 0; i + 1 < b; ++i)
        ret = min(ret, a[i+1]);
    return ret;
}

#endif // EX02_HPP
