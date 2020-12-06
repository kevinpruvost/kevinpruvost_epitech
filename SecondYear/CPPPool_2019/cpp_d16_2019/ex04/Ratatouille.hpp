/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef RATATOUILLE_HPP
#define RATATOUILLE_HPP

#include <string>
#include <ostream>
#include <sstream>

class Ratatouille
{
public:
    Ratatouille();
    Ratatouille(Ratatouille const &other);
    ~Ratatouille();
    Ratatouille &operator =(const Ratatouille &rhs);

    Ratatouille &addVegetable(unsigned  char);
    Ratatouille &addCondiment(unsigned  int);
    Ratatouille &addSpice(double);
    Ratatouille &addSauce(const  std:: string  &);

    std::string  kooc();

public:
    std::ostringstream _recipeStream;
};

#endif // RATATOUILLE_HPP
