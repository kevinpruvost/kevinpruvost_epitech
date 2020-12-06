/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "SickKoalaList.hpp"

// C++ includes
#include <iostream>

SickKoalaList::SickKoalaList(SickKoala * koala)
    : _koala { koala }
    , _next  { nullptr }
{
}

SickKoalaList::~SickKoalaList()
{
}

bool SickKoalaList::isEnd()
{
    if (!_next)
        return true;
    return false;
}

void SickKoalaList::append(SickKoalaList * list)
{
    if (!list)
        return;
    if (_next == nullptr)
        _next = list;
    else
        _next->append(list);
    list->setNext(nullptr);
}

SickKoala * SickKoalaList::getFromName(const std::string name)
{
    if (!_koala)
        return nullptr;
    if (_koala->getName() == name)
        return _koala;
    if (!_next)
        return nullptr;
    return _next->getFromName(name);
}

SickKoalaList * SickKoalaList::remove(SickKoalaList * ptr)
{
    if (!ptr)
        return this;
    if (this == ptr)
    {
        const auto next = _next;
        this->_next = nullptr;
        return next;
    }
    if (_next == ptr)
    {
        _next = _next->getNext();
        return this;
    }
    if (_next != nullptr)
    {
        if (_next->remove(ptr) != nullptr)
            return this;
    }
    return nullptr;
}

SickKoalaList * SickKoalaList::removeFromName(const std::string name)
{
    if (!_koala)
        return nullptr;
    if (_koala->getName() == name)
        return _next;
    if (_next->getKoalaName() == name)
    {
        _next = _next->getNext();
        return this;
    }
    if (_next != nullptr)
    {
        if (_next->removeFromName(name) != nullptr)
            return this;
    }
    return nullptr;
}

void SickKoalaList::dumpName()
{
    if (_koala != nullptr)
        std::cout << _koala->getName();
    else
        std::cout << "nullptr";

    if (_next == nullptr)
    {
        std::cout << ".";
        return;
    }
    std::cout << ", ";
    _next->dumpName();
}

void SickKoalaList::dump()
{
    std::cout << "Patients: ";
    dumpName();
    std::cout << std::endl;
}

SickKoala * SickKoalaList::getContent()
{
    return _koala;
}

SickKoalaList * SickKoalaList::getNext()
{
    return _next;
}

std::string SickKoalaList::getKoalaName()
{
    if (!_koala)
        return std::string();
    return _koala->getName();
}

void SickKoalaList::setNext(SickKoalaList * ptr)
{
    if (ptr == this)
        return;
    _next = ptr;
}
