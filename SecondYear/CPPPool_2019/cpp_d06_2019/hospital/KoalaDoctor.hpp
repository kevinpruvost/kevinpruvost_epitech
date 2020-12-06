/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#ifndef KOALADOCTOR_HPP
#define KOALADOCTOR_HPP

// Project includes
#include "KoalaNurse.hpp"

// C++ includes
#include <string>

class KoalaDoctor
{
public:
    KoalaDoctor(std::string name);
    ~KoalaDoctor();

private:
    std::string _name;
    bool        _isWorking;

private:
    void say(const std::string str);

public:
    void timeCheck();
    void diagnose(SickKoala * sick);

public:
    std::string getName();
};

#endif // KOALADOCTOR_HPP
