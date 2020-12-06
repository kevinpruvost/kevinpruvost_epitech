/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Admiral.hpp"

// C++ includes
#include <iostream>

Federation::Starfleet::Admiral::Admiral(std::string name)
    : _movePtr ( &Federation::Starfleet::Ship::move )
    , _firePtr ( &Federation::Starfleet::Ship::fire )
    , _name { name }
{
    std::cout << "Admiral " << name << " ready for action.\n";
}

void Federation::Starfleet::Admiral::fire(Federation::Starfleet::Ship * ship,
                                          Borg::Ship * target)
{
    if (!_firePtr || !ship || !target)
        return;
    std::cout << "On order from Admiral " << _name << ":\n";
    (ship->*_firePtr)(target);
}

bool Federation::Starfleet::Admiral::move(Federation::Starfleet::Ship * ship,
                                          Destination dest)
{
    if (!_movePtr || !ship)
        return false;
    return (ship->*_movePtr)(dest);
}
