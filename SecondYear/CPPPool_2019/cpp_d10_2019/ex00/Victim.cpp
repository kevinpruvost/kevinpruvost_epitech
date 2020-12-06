/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Victim.hpp"

Victim::Victim(const std::string & name)
    : _name { name }
{
    std::cout << "Some random victim called " << name << " just popped!\n";
}

//Victim::Victim()
//{
//}

Victim::~Victim()
{
    std::cout << "Victim " << _name << " just died for no apparent reason!\n";
}

void Victim::say(const std::string & str) const
{
    std::cout << _name << ", " << str << std::endl;
}

void Victim::getPolymorphed() const
{
    std::cout << _name << " has been turned into a cute little sheep!\n";
}

// Getters and setters ---------------------------------------------------------

std::string Victim::getName() const { return _name; }

void Victim::setName(const std::string & name) { _name = name; }

// Stand-alone operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, const Victim & victim)
{
    os << "I'm " << victim.getName() << " and I like otters!\n";
    return os;
}
