/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Federation.hpp"

// C++ includes
#include <iostream>

class Borg::Ship : public ShipBase
{
};

// Federation::Starfleet::Ship -------------------------------------------------

Federation::Starfleet::Ship::Ship(int length, int width,
                            std::string name, short maxWarp, int torpedo)
    : ShipBase(maxWarp, torpedo)
    , _length  { length  }
    , _width   { width   }
    , _name    { name    }
    , _captain { nullptr }
{
    _home = Destination::EARTH;
    _location = _home;
    std::cout << "The ship USS " << name << " has been finished.\n"
              << "It is " << length << " m in length and " << width
              << " m in width.\n"
              << "It can go to Warp " << maxWarp << "!\n";
    if (torpedo != 0)
        std::cout << "Weapons are set: " << torpedo << " torpedoes ready.\n";
}

Federation::Starfleet::Ship::~Ship()
{
}

void Federation::Starfleet::Ship::say(const std::string str)
{
    std::cout << "USS " << _name << ": " << str << std::endl;
}

void Federation::Starfleet::Ship::setupCore(WarpSystem::Core * core)
{
    if (!core)
        return;
    _core = core;
    say("The core is set.");
}

void Federation::Starfleet::Ship::checkCore()
{
    if (!_core || !_core->checkReactor())
        return;
    std::string resp("The core is ");
    resp.append( (_core->checkReactor()->isStable()) ? "stable" : "unstable" );
    resp.append(" at the time.");
    say(resp);
}

void Federation::Starfleet::Ship::promote(
        Federation::Starfleet::Captain * captain)
{
    if (!captain)
        return;
    std::string str = "I'm glad to be the captain of the USS ";
    str.append(_name);
    str.append(".");

    _captain = captain;
    captain->say(str);
}

void Federation::Starfleet::Ship::fire(Borg::Ship * target)
{
    fire(1, target);
}

void Federation::Starfleet::Ship::fire(int torpedoes, Borg::Ship * target)
{
    if (!target)
        return;
    _photonTorpedo -= torpedoes;
    std::cout << _name << ": Firing on target. " << _photonTorpedo
              << " torpedoes remaining.\n";

    const int torpedoFired = (_photonTorpedo < 0) ? _photonTorpedo
                                                  : torpedoes;

    if (_photonTorpedo == 0)
    {
        std::cout << _name << ": No more torpedo to fire, "
                  << _captain->getName() << "!\n";
    }
    else if (_photonTorpedo < 0)
    {
        _photonTorpedo = 0;
        std::cout << _name << ": No enough torpedoes to fire, "
                  << _captain->getName() << "!\n";
    }
    target->setShield(target->getShield() - (50 * torpedoFired));
}

// Federation::Starfleet::Captain ----------------------------------------------

Federation::Starfleet::Captain::Captain(std::string name)
    : _name { name }
{
}

Federation::Starfleet::Captain::~Captain()
{
}

std::string Federation::Starfleet::Captain::getName()
{
    return _name;
}

int Federation::Starfleet::Captain::getAge()
{
    return _age;
}

void Federation::Starfleet::Captain::setAge(int age)
{
    _age = age;
}

void Federation::Starfleet::Captain::say(const std::string str)
{
    std::cout << _name << ": " << str << std::endl;
}

// Federation::Starfleet::Ensign ----------------------------------------------------------------------

Federation::Starfleet::Ensign::Ensign(std::string name)
    : _name { name }
{
    std::cout << "Ensign " << name << ", awaiting orders.\n";
}


// Independent Ship ------------------------------------------------------------

Federation::Ship::Ship(int length, int width, std::string name)
    : ShipBase(1)
    , _length  { length  }
    , _width   { width   }
    , _name    { name    }
{
    _home = Destination::VULCAN;
    _location = _home;
    std::cout << "The independent ship " << name <<
                 " just finished its construction.\n"
              << "It is " << length << " m in length and " << width
              << " m in width.\n";
}

Federation::Ship::~Ship()
{
}

void Federation::Ship::say(const std::string str)
{
    std::cout << _name << ": " << str << std::endl;
}

void Federation::Ship::setupCore(WarpSystem::Core * core)
{
    if (!core)
        return;
    _core = core;
    say("The core is set.");
}

void Federation::Ship::checkCore()
{
    if (!_core || !_core->checkReactor())
        return;
    std::string resp("The core is ");
    resp.append( (_core->checkReactor()->isStable()) ? "stable" : "unstable" );
    resp.append(" at the time.");
    say(resp);
}

WarpSystem::Core * Federation::Ship::getCore()
{
    return _core;
}
