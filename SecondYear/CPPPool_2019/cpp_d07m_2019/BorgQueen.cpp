/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "BorgQueen.hpp"

// C++ includes
#include <iostream>

Borg::BorgQueen::BorgQueen()
    : _movePtr    { &Borg::Ship::move }
    , _firePtr    { &Borg::Ship::fire }
    , _destroyPtr { &Borg::Ship::fire }
{
}

void Borg::BorgQueen::fire(Borg::Ship * ship, Federation::Starfleet::Ship * target)
{
    if (!_firePtr || !ship || !target)
        return;
    (ship->*_firePtr)(target);
}

bool Borg::BorgQueen::move(Borg::Ship * ship, Destination dest)
{
    if (!_movePtr || !ship)
        return false;
    return (ship->*_movePtr)(dest);
}

void Borg::BorgQueen::destroy(Borg::Ship * ship, Federation::Ship * target)
{
    if (!_destroyPtr || !ship || !target)
        return;
    (ship->*_destroyPtr)(target);
}
