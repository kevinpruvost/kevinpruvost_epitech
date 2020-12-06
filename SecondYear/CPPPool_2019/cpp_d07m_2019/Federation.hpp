/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#pragma once

// Project includes
#include "WarpSystem.hpp"

// C++ includes
#include <string>

// Starfleet Ship --------------------------------------------------------------

class Federation::Starfleet::Ship : public ShipBase
{
public:
    Ship(int length, int width, std::string name, short maxWarp,
         int torpedo = 0);
    ~Ship();

public:
    void setupCore(WarpSystem::Core * core);
    void checkCore();
    void promote(Federation::Starfleet::Captain * captain);

    void fire(Borg::Ship * target);
    void fire(int torpedoes, Borg::Ship * target);

private:
    void say(const std::string str);

private:
    int         _length;
    int         _width;
    std::string _name;

    Federation::Starfleet::Captain * _captain;
};

// Starfleet Captain -----------------------------------------------------------

class Federation::Starfleet::Captain
{
public:
    Captain(std::string name);
    ~Captain();

public:
    std::string getName();
    int getAge();
    void setAge(int age);
    void say(const std::string str);

private:
    std::string _name;
    int         _age = 0;
};

// Ensign ----------------------------------------------------------------------

class Federation::Starfleet::Ensign
{
public:
    Ensign(std::string name);

private:
    std::string _name;
};

// Independent Ship ------------------------------------------------------------

class Federation::Ship : public ShipBase
{
public:
    Ship(int length, int width, std::string name);
    ~Ship();

public:
    void setupCore(WarpSystem::Core * core);
    void checkCore();
    WarpSystem::Core * getCore();

private:
    void say(const std::string str);

private:
    int         _length;
    int         _width;
    std::string _name;
};
