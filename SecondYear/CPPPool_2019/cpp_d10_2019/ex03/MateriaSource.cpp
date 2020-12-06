/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
}

MateriaSource::~MateriaSource()
{
    for (const auto part : _memory)
        delete part;
}

void MateriaSource::learnMateria(AMateria * materia)
{
    if (_memory.size() >= 4)
        return;

    _memory.push_back(materia);
}

AMateria * MateriaSource::createMateria(const std::string &type)
{
    for (const auto part : _memory)
    {
        if (part->getType() == type)
            return part->clone();
    }
    return nullptr;
}
