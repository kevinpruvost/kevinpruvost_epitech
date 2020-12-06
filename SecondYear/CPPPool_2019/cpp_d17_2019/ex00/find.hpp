/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/31
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef FIND_HPP
#define FIND_HPP

#include <algorithm>
#include <list>

template<class T, typename U = int>
typename T::iterator do_find(T & temp, int search)
{
    return std::find(temp.begin(), temp.end(), search);
}

#endif // FIND_HPP
