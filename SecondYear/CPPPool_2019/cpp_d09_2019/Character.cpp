/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/23
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Character.hpp"

// C++ includes
#include <iostream>
#include <ostream>

Character::Character(const std::string &name, int level,
                     const std::string classs, const std::string race,
                     int pv, int power, int strength, int stamina,
                     int intelligence, int spirit, int agility,
                     AttackRange range)
    : Range         { range        }
    , _lvl          { level        }
    , _pv           { pv           }
    , _power        { power        }
    , _name         { name         }
    , _class        { classs       }
    , _race         { race         }
    , _strength     { strength     }
    , _stamina      { stamina      }
    , _intelligence { intelligence }
    , _spirit       { spirit       }
    , _agility      { agility      }
{
    say("Created");
}

void Character::say(const std::string str) const
{
    std::cout << _name << " " << str << std::endl;
}

bool Character::checkAndUsePower(const int cost)
{
    if (cost > _power)
    {
        say("out of power");
        return false;
    }
    _power -= cost;
    return true;
}

int Character::CloseAttack()
{
    if (Range != Character::CLOSE)
        return 0;

    if (!checkAndUsePower(10))
        return 0;

    const int attack = 10 + _strength;
    say("strikes with a wooden stick");
    return attack;
}

int Character::RangeAttack()
{
    if (Range != Character::RANGE)
        return 0;

    if (!checkAndUsePower(10))
        return 0;

    const int attack = 5 + _strength;
    say("tosses a stone");
    return attack;
}

void Character::Heal()
{
    _pv += 50;
    if (_pv > 100)
        _pv = 100;
    say("takes a potion");
}

void Character::RestorePower()
{
    _power += 100;
    if (_power > 100)
        _power = 100;
    say("eats");
}

void Character::TakeDamage(int damage)
{
    _pv -= damage;
    if (_pv <= 0)
        say("out of combat");
    else
    {
        std::cout << _name << " " << "takes " << damage
                  << " damage" << std::endl;
    }
}

// Getters and setters ---------------------------------------------------------

int Character::getLvl() const { return _lvl; }

int Character::getPv() const { return _pv; }

int Character::getPower() const { return _power; }

int Character::getStrength() const { return _strength; }

int Character::getStamina() const { return _stamina; }

int Character::getIntelligence() const { return _intelligence; }

int Character::getSpirit() const { return _spirit; }

int Character::getAgility() const { return _agility; }

std::string Character::getClass() const { return _class; }

std::string Character::getRace() const { return _race; }

const std::string & Character::getName() const { return _name; }

void Character::setLvl(int lvl) { _lvl = lvl; }

void Character::setPv(int pv)
{
    _pv = pv;
    if (_pv < 0)
        _pv = 0;
    if (_pv > 100)
        _pv = 100;
}

void Character::setPower(int power) { _power = power; }

void Character::setStrength(int strength) { _strength = strength; }

void Character::setStamina(int stamina) { _stamina = stamina; }

void Character::setIntelligence(int intel) { _intelligence = intel; }

void Character::setSpirit(int spirit) { _spirit = spirit; }

void Character::setAgility(int agi) { _agility = agi; }

// Stand-alone operators -------------------------------------------------------

std::ostream & operator<<(std::ostream & os, const Character & oof)
{
    os << "Name :            " << oof.getName() << std::endl;
    os << "Lvl :             " << oof.getLvl() << std::endl;
    os << "Class :           " << oof.getClass() << std::endl;
    os << "Race :            " << oof.getRace() << std::endl;
    os << "Strength :        " << oof.getStrength() << std::endl;
    os << "Health :          " << oof.getPv() << std::endl;
    os << "Power :           " << oof.getPower() << std::endl;
    os << "Stamina :         " << oof.getStamina() << std::endl;
    os << "Intelligence :    " << oof.getIntelligence() << std::endl;
    os << "Spirit :          " << oof.getSpirit() << std::endl;
    os << "Agility :         " << oof.getAgility() << std::endl;
    return os;
}
