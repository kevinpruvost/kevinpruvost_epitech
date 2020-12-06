/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/28
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Fruit.hpp"

Fruit::Fruit(const int vitamins, const std::string & name)
    : _vitamins { vitamins }
    , _name { name }
{
}

Fruit::Fruit()
{
}

Fruit::~Fruit()
{
}

int Fruit::getVitamins() const { return _vitamins; }

std::string Fruit::getName() const { return _name; }

void Fruit::setName(const std::string &name) { _name = name; }

void Fruit::setVitamins(const int vitamins) { _vitamins = vitamins; }
