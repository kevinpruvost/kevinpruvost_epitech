/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

#include <vector>

class MateriaSource : virtual public IMateriaSource
{
public:
    MateriaSource();
    ~MateriaSource();

public:
    void learnMateria(AMateria * materia) override;
    AMateria * createMateria(const std::string & type) override;

private:
    std::vector<AMateria *> _memory;
};

#endif // MATERIASOURCE_HPP
