/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

// Project includes
#include "Borg.hpp"

namespace Borg
{
    class BorgQueen;
}

#pragma once

class Borg::BorgQueen
{
public:
    BorgQueen();

public:
    bool (Borg::Ship::*_movePtr)(Destination);
    void (Borg::Ship::*_firePtr)(Federation::Starfleet::Ship *);
    void (Borg::Ship::*_destroyPtr)(Federation::Ship *);

    void fire(Borg::Ship * ship, Federation::Starfleet::Ship * target);
    bool move(Borg::Ship * ship, Destination dest);
    void destroy(Borg::Ship * ship, Federation::Ship * target);
};
