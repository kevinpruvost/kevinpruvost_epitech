/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Sorcerer.hpp"

Sorcerer::Sorcerer(const std::string & name, const std::string & title)
    : _name  { name  }
    , _title { title }
{
    say("is born!");
}

Sorcerer::~Sorcerer()
{
    say("is dead. Consequences will never be the same!");
}

void Sorcerer::say(const std::string & str) const
{
    std::cout << _name << ", " << _title << ", " << str << std::endl;
}

void Sorcerer::polymorph(const Victim & victim) const
{
    victim.getPolymorphed();
}

// Getters and setters ---------------------------------------------------------

std::string Sorcerer::getName() const { return _name; }

std::string Sorcerer::getTitle() const { return _title; }

// Stand-alone operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, const Sorcerer & sorcerer)
{
    os << "I am " << sorcerer.getName() << ", " << sorcerer.getTitle()
       << ", and I like ponies!\n";
    return os;
}
