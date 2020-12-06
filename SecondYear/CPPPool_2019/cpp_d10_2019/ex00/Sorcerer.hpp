/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef SORCERER_HPP
#define SORCERER_HPP

// Project includes
#include "Victim.hpp"

// C++ includes
#include <string>
#include <iostream>

class Sorcerer
{
public:
    Sorcerer(const std::string & name, const std::string & title);
    ~Sorcerer();

public:
    void say(const std::string & str) const;
    void polymorph(const Victim & victim) const;

public:
    std::string getName() const;
    std::string getTitle() const;

private:
    std::string _name;
    std::string _title;
};

std::ostream & operator<<(std::ostream & os, const Sorcerer & sorcerer);

#endif // SORCERER_HPP
