/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Toy.hpp"

Toy::Toy()
    : _type { Toy::ToyType::BASIC_TOY }
    , _name ("toy")
    , _picture ("")
{
}

Toy::Toy(ToyType type, const std::string &name, const std::string &file)
    : _type { type }
    , _name { name }
    , _picture (file)
{
}

Toy::ToyType Toy::getType() const
{
    return _type;
}

std::string Toy::getName() const
{
    return _name;
}

std::string Toy::getAscii() const
{
    return _picture.data;
}

void Toy::setName(const std::string & name)
{
    _name = name;
}

bool Toy::setAscii(const std::string & file)
{
    return _picture.getPictureFromFile(file);
}
