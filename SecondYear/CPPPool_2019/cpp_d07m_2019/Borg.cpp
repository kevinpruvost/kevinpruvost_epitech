/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Borg.hpp"

// C++ includes
#include <iostream>

Borg::Ship::Ship(int weaponFrequency, short repair)
    : ShipBase         { 9 }
    , _side            { 300 }
    , _weaponFrequency { weaponFrequency }
    , _repair          { repair }
{
    _home = Destination::UNICOMPLEX;
    _location = _home;
    std::cout << "We are the Borgs. Lower your shields and surrender "
              << "yourselves unconditionally.\n"
              << "Your biological characteristics and technologies will "
              << "be assimilated.\n"
              << "Resistance is futile.\n";
}

Borg::Ship::~Ship()
{
}

void Borg::Ship::setupCore(WarpSystem::Core * core)
{
    if (!core)
        return;
    _core = core;
}

void Borg::Ship::checkCore()
{
    if (!_core || !_core->checkReactor())
        return;
    std::string resp = (_core->checkReactor()->isStable()) ?
                "Everything is in order."
              : "Critical failure imminent.";
    std::cout << resp << std::endl;
}

int Borg::Ship::getWeaponFrequency()
{
    return _weaponFrequency;
}

void Borg::Ship::setWeaponFrequency(int freq)
{
    _weaponFrequency = freq;
}

void Borg::Ship::fire(Federation::Starfleet::Ship * target)
{
    if (!target)
        return;
    target->setShield(target->getShield() - _weaponFrequency);

    std::cout << "Firing on target with " << _weaponFrequency
              << "GW frequency.\n";
}

void Borg::Ship::fire(Federation::Ship * target)
{
    if (!target || !target->getCore() || !target->getCore()->checkReactor())
        return;
    target->getCore()->checkReactor()->setStability(false);
    std::cout << "Firing on target with " << _weaponFrequency
              << "GW frequency.\n";
}

void Borg::Ship::repair()
{
    if (_repair > 0)
    {
        _shield = 100;
        --_repair;
        std::cout << "Begin shield re-initialisation... Done. Awaiting"
                  << " further instructions.\n";
    }
    else
        std::cout << "Energy cells depleted, shield weakening.\n";
}
