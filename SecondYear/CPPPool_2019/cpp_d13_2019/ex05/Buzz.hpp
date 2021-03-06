/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef BUZZ_HPP
#define BUZZ_HPP

#include "Toy.hpp"

class Buzz : public Toy
{
public:
    Buzz(const std::string & name, const std::string & ascii = "buzz.txt");

public:
    bool speak(const std::string &str) override;
    bool speak_es(const std::string &str) override;
};

#endif // BUZZ_HPP
