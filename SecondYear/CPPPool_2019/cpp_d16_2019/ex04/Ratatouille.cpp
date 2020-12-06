/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Ratatouille.hpp"

Ratatouille::Ratatouille()
{
}

Ratatouille::Ratatouille(Ratatouille const &other)
{
    _recipeStream.str("");
    _recipeStream << other._recipeStream.str();
}

Ratatouille::~Ratatouille()
{
}

Ratatouille &Ratatouille::operator=(const Ratatouille &rhs)
{
    _recipeStream.str("");
    _recipeStream << rhs._recipeStream.str();
    return *this;
}

Ratatouille &Ratatouille::addVegetable(unsigned char nb)
{
    _recipeStream << nb;

    return *this;
}

Ratatouille &Ratatouille::addCondiment(unsigned int nb)
{
    _recipeStream << nb;

    return *this;
}

Ratatouille &Ratatouille::addSpice(double nb)
{
    _recipeStream << nb;

    return *this;
}

Ratatouille &Ratatouille::addSauce(const std::string & str)
{
    _recipeStream << str;

    return *this;
}

std::string Ratatouille::kooc()
{
    return _recipeStream.str();
}
