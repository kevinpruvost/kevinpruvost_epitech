/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef WOODY_HPP
#define WOODY_HPP

#include "Toy.hpp"

class Woody : public Toy
{
public:
    Woody(const std::string & name, const std::string & ascii = "woody.txt");
};

#endif // WOODY_HPP
