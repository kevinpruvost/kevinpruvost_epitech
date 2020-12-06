/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "KoalaNurseList.hpp"

// C++ includes
#include <iostream>

KoalaNurseList::KoalaNurseList(KoalaNurse * koala)
    : _koala { koala }
    , _next  { nullptr }
{
}

KoalaNurseList::~KoalaNurseList()
{
}

bool KoalaNurseList::isEnd()
{
    if (!_next)
        return true;
    return false;
}

void KoalaNurseList::append(KoalaNurseList * list)
{
    if (!list)
        return;
    if (_next == nullptr)
        _next = list;
    else
        _next->append(list);
    list->setNext(nullptr);
}

KoalaNurse * KoalaNurseList::getFromID(const int id)
{
    if (!_koala)
        return nullptr;
    if (_koala->getID() == id)
        return _koala;
    if (!_next)
        return nullptr;
    return _next->getFromID(id);
}

KoalaNurseList * KoalaNurseList::remove(KoalaNurseList * ptr)
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

KoalaNurseList * KoalaNurseList::removeFromID(const int id)
{
    if (!_koala)
        return nullptr;
    if (_koala->getID() == id)
        return _next;
    if (_next->getKoalaID() == id)
    {
        _next = _next->getNext();
        return this;
    }
    if (_next != nullptr)
    {
        if (_next->removeFromID(id) != nullptr)
            return this;
    }
    return nullptr;
}

void KoalaNurseList::dumpID()
{
    if (_koala != nullptr)
        std::cout << _koala->getID();
    else
        std::cout << "nullptr";

    if (_next == nullptr)
    {
        std::cout << ".";
        return;
    }
    std::cout << ", ";
    _next->dumpID();
}

void KoalaNurseList::dump()
{
    std::cout << "Nurses: ";
    dumpID();
    std::cout << std::endl;
}

KoalaNurse * KoalaNurseList::getContent()
{
    return _koala;
}

KoalaNurseList * KoalaNurseList::getNext()
{
    if (!_next)
        return nullptr;
    return _next;
}

int KoalaNurseList::getKoalaID()
{
    if (!_koala)
        return 0;
    return _koala->getID();
}

void KoalaNurseList::setNext(KoalaNurseList * ptr)
{
    if (this == ptr)
        return;
    _next = ptr;
}

void KoalaNurseList::timeCheck()
{
    if (_koala)
        _koala->timeCheck();
}

std::string KoalaNurseList::readReport(const std::string fileName)
{
    if (_koala)
        return _koala->readReport(fileName);
    return std::string();
}

void KoalaNurseList::heal(SickKoalaList * koala)
{
    if (!_koala)
        return;
    std::string filename = koala->getKoalaName();
    filename.append(".report");
    const std::string medic = _koala->readReport(filename);
    _koala->giveDrug(medic, koala->getContent());
}
