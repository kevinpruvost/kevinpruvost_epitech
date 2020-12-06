/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SQUAD_HPP
#define SQUAD_HPP

// Project includes
#include "ISquad.hpp"

// C++ includes
#include <vector>

class Squad : virtual public ISquad
{
public:
    Squad();
    Squad(ISquad & otherSquad);
    ~Squad();

public:
    int getCount() const override;
    ISpaceMarine * getUnit(int id) override;
    int push(ISpaceMarine * marine) override;

    Squad & operator=(ISquad & otherSquad);

private:
   std::vector<ISpaceMarine *> _marines;
};

#endif // SQUAD_HPP
