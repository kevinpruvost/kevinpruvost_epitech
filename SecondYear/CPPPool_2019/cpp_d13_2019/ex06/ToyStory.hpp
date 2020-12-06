/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/27
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef TOYSTORY_HPP
#define TOYSTORY_HPP

#include "Buzz.hpp"
#include "Woody.hpp"

class ToyStory
{
public:
    ToyStory();

public:
    static void tellMeAStory(const std::string & story,
                             Toy & toy1,
                             bool (Toy::*func1)(const std::string &),
                             Toy & toy2,
                             bool (Toy::*func2)(const std::string &));
    static bool actionStory(Toy & toy, const std::string & s,
                            bool (Toy::*func1)(const std::string &));
};

#endif // TOYSTORY_HPP
