/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "SickKoala.hpp"

// C++ includes
#include <iostream>

SickKoala::SickKoala(std::string name)
    : _name { name }
{
}

SickKoala::~SickKoala()
{
    say("Kreooogg!! I'm cuuuured!");
}

void SickKoala::say(const std::string str)
{
    std::cout << "Mr." << _name << ": " << str << std::endl;
}

void SickKoala::poke()
{
    say("Gooeeeeerrk!!");
}

bool SickKoala::takeDrug(std::string string)
{
    if (string == "Mars")
    {
        say("Mars, and it kreogs!");
        return true;
    }
    else if (string == "Buronzand")
    {
        say("And you'll sleep right away!");
        return true;
    }
    else
        say("Goerkreog!");
    return false;
}

void SickKoala::overDrive(std::string string)
{
    size_t index = 0;
    while (true)
    {
         index = string.find("Kreog!", index);
         if (index == std::string::npos)
             break;
         string.replace(index, 6, "1337!");
         index += 5;
    }
    say(string);
}

std::string SickKoala::getName()
{
    return _name;
}
