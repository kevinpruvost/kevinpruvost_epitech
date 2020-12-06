/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX00_HPP
#define EX00_HPP

namespace
{
    template <typename T>
    void swap(T & a, T & b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    T min(T a, T b)
    {
        if (a < b)
            return a;
        return b;
    }

    template <typename T>
    T max(T a, T b)
    {
        if (a < b)
            return b;
        return a;
    }

    template <typename T>
    T add(T a, T b) { return a + b; }
}

#endif // EX00_HPP
