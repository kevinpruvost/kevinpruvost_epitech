/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "KoalaDoctor.hpp"

// C++ includes
#include <iostream>
#include <random>
#include <fstream>

KoalaDoctor::KoalaDoctor(std::string name)
    : _name { name }
    , _isWorking { false }
{
    std::string cst("I'm Dr.");
    cst.append(_name);
    cst.append("! How do you kreog?");
    say(cst);
}

KoalaDoctor::~KoalaDoctor()
{
}

void KoalaDoctor::say(const std::string str)
{
    std::cout << "Dr." << _name << ": " << str << std::endl;
}

void KoalaDoctor::diagnose(SickKoala * sick)
{
    if (!sick)
        return;
    std::string resp("So what's goerking you Mr.");
    resp.append(sick->getName());
    resp.append("?");
    say(resp);
    sick->poke();

    // Writes the report.
    std::ofstream file((sick->getName()).append(".report"));
    std::string tab[5] = {"Mars", "Buronzand", "Viagra",
                          "Extasy", "Eucalyptus leaf"};
    std::string rep = tab[std::rand() % 5];

    file.write(rep.c_str(), rep.length());
    file.close();
}

void KoalaDoctor::timeCheck()
{
    if (!_isWorking)
    {
        say("Time to get to work!");
        _isWorking = true;
    }
    else
    {
        say("Time to go home to my eucalyptus forest!");
        _isWorking = false;
    }
}

std::string KoalaDoctor::getName()
{
    return _name;
}
