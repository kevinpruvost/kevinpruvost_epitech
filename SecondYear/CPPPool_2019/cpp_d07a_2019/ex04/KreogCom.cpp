/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/21
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "KreogCom.hpp"

// C++ includes
#include <iostream>

KreogCom::KreogCom(int x, int y, int serial)
    : m_serial { serial }
    , _x       { x }
    , _y       { y }
{
    std::cout << "KreogCom " << serial << " initialized\n";
}

KreogCom::~KreogCom()
{
    std::cout << "KreogCom " << m_serial << " shutting down\n";
}

void KreogCom::setCom(KreogCom * com)
{
    _com = com;
}

void KreogCom::addCom(int x, int y, int serial)
{
    KreogCom * newCom = new KreogCom(x, y, serial);

    if (_com)
        newCom->setCom(_com);
    _com = newCom;
}

KreogCom * KreogCom::getCom()
{
    if (!_com)
        return nullptr;
    return _com;
}

void KreogCom::removeCom()
{
    if (_com)
    {
        KreogCom * del = _com;
        if (_com->getCom())
        {
            del = _com;
            _com = _com->getCom();
        }
        else
            _com = nullptr;
        delete del;
    }
}

void KreogCom::ping()
{
    std::cout << "KreogCom " << m_serial << " currently at "
              << _x << " " << _y << std::endl;
}

void KreogCom::locateSquad()
{
    KreogCom * com = _com;
    while (com)
    {
        com->ping();
        com = com->getCom();
    }
    ping();
}
