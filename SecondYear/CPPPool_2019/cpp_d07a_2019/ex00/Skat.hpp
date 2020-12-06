/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef SKAT_HPP
#define SKAT_HPP

#include <string>

class Skat
{
public:
    Skat(const std::string & name = "bob", int stimPak = 15);
    ~Skat();

public:
    int stimPaks();
    const std::string & name();

public:
    void shareStimPaks(int number, int & stock);
    void addStimPaks(unsigned int number);
    void useStimPaks();
    void status();

private:
    std::string _name;
    int         _stimPaksNb;
};

#endif // SKAT_HPP
