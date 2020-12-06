/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "Buzz.hpp"

Buzz::Buzz(const std::string & name, const std::string & ascii)
{
    setName(name);
    setAscii(ascii);
}

bool Buzz::speak(const std::string & str)
{
    std::cout << "BUZZ: " << getName() << " \"" << str << "\"" << std::endl;
    return true;
}


bool Buzz::speak_es(const std::string & str)
{
    std::cout << "BUZZ: " << getName() << " senorita \"" << str
              << "\" senorita" << std::endl;
    return true;
}
