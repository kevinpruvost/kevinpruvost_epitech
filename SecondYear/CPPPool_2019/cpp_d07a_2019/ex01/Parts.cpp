/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Parts.hpp"

// C++ includes
#include <iostream>

class KoalaBot
{
    void setParts(const Arms & arms);
    void setParts(const Legs & legs);
    void setParts(const Head & head);

    void swapParts(const Arms & arms);
    void swapParts(const Legs & legs);
    void swapParts(const Head & head);
};

// Parts -----------------------------------------------------------------------

Parts::Parts(const std::string && name, bool functional)
    : _name { name }
    , _functionnal { functional }
{
}

Parts::Parts(const std::string & name, bool functional)
    : _name { name }
    , _functionnal { functional }
{
}

bool Parts::isFunctionnal()
{
    return _functionnal;
}

std::string Parts::serial()
{
    return _name;
}

void Parts::informationsTemp(const std::string className)
{
    std::cout << "[Parts] " << className << " " << _name << " status : "
              << ((_functionnal) ? "OK" : "KO") << std::endl;
}

// Head ------------------------------------------------------------------------

Head::Head(const std::string & string, bool functionnal)
    : Parts(string, functionnal)
{
}

void Head::informations()
{
    informationsTemp("Head");
}

// Arms ------------------------------------------------------------------------

Arms::Arms(const std::string & string, bool functionnal)
    : Parts(string, functionnal)
{

}

void Arms::informations()
{
    informationsTemp("Arms");
}

// Legs ------------------------------------------------------------------------

Legs::Legs(const std::string & string, bool functionnal)
    : Parts(string, functionnal)
{

}

void Legs::informations()
{
    informationsTemp("Legs");
}
