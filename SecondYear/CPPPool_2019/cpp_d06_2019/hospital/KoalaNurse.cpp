/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "KoalaNurse.hpp"

// C++ includes
#include <iostream>
#include <fstream>

KoalaNurse::KoalaNurse(int id)
    : _id        { id }
    , _isWorking { false }
{    
}

KoalaNurse::~KoalaNurse()
{
    say("Finally some rest!");
}

void KoalaNurse::say(const std::string str)
{
    std::cout << "Nurse " << _id << ": " << str << std::endl;
}

void KoalaNurse::giveDrug(const std::string str, SickKoala * sick)
{
    sick->takeDrug(str);
}

std::string KoalaNurse::readReport(const std::string fileName)
{
    std::string medicName;

    if (fileName.find(".report") == std::string::npos)
        return medicName;
    if (fileName.size() <= 7)
        return medicName;
    std::ifstream f1(fileName);
    if (!f1.is_open())
        return medicName;
    std::string s;
    std::getline(f1, s);
    f1.close();

    std::string patientName = fileName.substr(0, fileName.find(".report"));
    std::string response("Kreog! Mr.");
    response.append(patientName);
    response.append(" needs a ");
    response.append(s);
    response.append("!");

    if (!s.empty())
        say(response);
    return s;
}

void KoalaNurse::timeCheck()
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

int KoalaNurse::getID()
{
    return _id;
}
