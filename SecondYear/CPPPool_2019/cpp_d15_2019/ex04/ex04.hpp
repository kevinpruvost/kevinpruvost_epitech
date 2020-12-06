/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef EX04_HPP
#define EX04_HPP

#include <string>

template<typename T>
int equal(const T & a, const T & b);
int equal(const char * a, const char * b);

template<typename T>
class Tester
{
public:
    Tester();

    int equal(const T & a, const T & b);
};

#endif // EX04_HPP
