/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Character.hpp"

Character::Character(const std::string & name)
    : _name { name }
{
}

Character::Character(Character & other)
    : _name { other.getName() }
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.getMateria(i))
            _materias[i] = other.getMateria(i)->clone();
    }
}

Character::~Character()
{
    for (int i = 0; i < 4; ++i)
    {
        if (_materias[i])
            delete _materias[i];
    }
}

Character & Character::operator=(Character & other)
{
    _name = other.getName();

    for (int i = 0; i < 4; ++i)
    {
        if (_materias[i])
            delete _materias[i];
        _materias[i] = nullptr;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (other.getMateria(i))
            _materias[i] = other.getMateria(i)->clone();
    }
    return *this;
}

const std::string & Character::getName() const
{
    return _name;
}

void Character::equip(AMateria * m)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (!_materias[i])
        {
            _materias[i] = m;
            return;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx < 0 || idx >= 4)
        return;
    _materias[idx] = nullptr;
}

void Character::use(int idx, ICharacter & target)
{
    if (idx < 0 || idx >= 4)
        return;
    _materias[idx]->use(target);
}

AMateria * Character::getMateria(int idx) const
{
    if (idx < 0 || idx >= 4)
        return nullptr;
    return _materias[idx];
}
