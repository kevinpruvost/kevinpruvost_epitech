/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "KoalaBot.hpp"

// C++ includes
#include <iostream>

KoalaBot::KoalaBot()
    : _name { "Bob-01" }
{

}

void KoalaBot::setParts(const Head & head)
{
    _head = head;
}

void KoalaBot::setParts(const Arms & arms)
{
    _arms = arms;
}

void KoalaBot::setParts(const Legs & legs)
{
    _legs = legs;
}

void KoalaBot::swapParts(Head & head)
{
    Head actualHead;
    _head = head;
    head = actualHead;
}

void KoalaBot::swapParts(Arms & arms)
{
    Arms actualArms;
    _arms = arms;
    arms = actualArms;
}

void KoalaBot::swapParts(Legs & legs)
{
    Legs actualLegs;
    _legs = legs;
    legs = actualLegs;
}

void KoalaBot::informations()
{
    std::cout << "[KoalaBot] " << _name << std::endl;
    std::cout << "     ";
    _arms.informations();
    std::cout << "     ";
    _legs.informations();
    std::cout << "     ";
    _head.informations();
}

bool KoalaBot::status()
{
    if (_arms.isFunctionnal() && _legs.isFunctionnal() && _head.isFunctionnal())
        return true;
    return false;
}
