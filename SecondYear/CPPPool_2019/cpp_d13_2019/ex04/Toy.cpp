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

Toy::Toy(const Toy & toy)
    : _type { toy.getType() }
    , _name { toy.getName() }
{
    _picture.data = toy.getAscii();
}

Toy::~Toy()
{
}

Toy & Toy::operator =(const Toy & toy)
{
    _name = toy.getName();
    _type = toy.getType();
    _picture.data = toy.getAscii();
    return *this;
}

bool Toy::speak(const std::string & str)
{
    std::cout << getName() << " \"" << str << "\"" << std::endl;
    return true;
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

void Toy::setPictureString(const std::string & str)
{
    _picture.setString(str);
}

Toy & Toy::operator <<(const std::string & str)
{
    setPictureString(str);
    return *this;
}

std::ostream & operator <<(std::ostream & os, const Toy & toy)
{
    os << toy.getName() << std::endl << toy.getAscii() << std::endl;
    return os;
}
