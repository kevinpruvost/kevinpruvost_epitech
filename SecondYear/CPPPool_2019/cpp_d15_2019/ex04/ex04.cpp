/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/29
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "ex04.hpp"

#include <cstring>

template class Tester<int>;
template class Tester<float>;
template class Tester<std::string>;
template class Tester<double>;

template<typename T>
Tester<T>::Tester() {}


template int Tester<int>::equal(const int & a, const int & b);
template int Tester<double>::equal(const double & a, const double & b);
template int Tester<float>::equal(const float & a, const float & b);
template int Tester<std::string>::equal(const std::string & a, const std::string & b);

template<typename T>
int Tester<T>::equal(const T &a, const T &b)
{
    if (a == b)
        return 1;
    return 0;
}


template int equal(const int & a, const int & b);
template int equal(const float & a, const float & b);
template int equal(const std::string & a, const std::string & b);
template int equal(const double & a, const double & b);

template<typename T>
int equal(const T & a, const T & b)
{
    if (a == b)
        return 1;
    return 0;
}

int equal(const char * a, const char * b)
{
    if (std::strcmp(a, b) == 0)
        return 1;
    return 0;
}
