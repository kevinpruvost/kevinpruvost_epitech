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
#include "Federation.hpp"

namespace Federation::Starfleet
{
    class Admiral;
}

class Federation::Starfleet::Admiral
{
public:
    Admiral(std::string name);

public:
    bool (Federation::Starfleet::Ship::*_movePtr)(Destination);
    void (Federation::Starfleet::Ship::*_firePtr)(Borg::Ship *);

    void fire(Federation::Starfleet::Ship * ship, Borg::Ship * target);
    bool move(Federation::Starfleet::Ship * ship, Destination dest);

private:
    std::string _name;
};
