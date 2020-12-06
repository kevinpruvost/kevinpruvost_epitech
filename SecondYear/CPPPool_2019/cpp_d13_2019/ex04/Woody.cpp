/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Woody.hpp"

Woody::Woody(const std::string & name, const std::string & ascii)
{
    setName(name);
    setAscii(ascii);
}

bool Woody::speak(const std::string & str)
{
    std::cout << "WOODY: " << getName() << " \"" << str << "\"" << std::endl;
    return true;
}
