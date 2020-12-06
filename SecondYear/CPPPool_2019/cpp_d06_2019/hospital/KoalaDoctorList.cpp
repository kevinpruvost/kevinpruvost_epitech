/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/20
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "KoalaDoctorList.hpp"

// C++ includes
#include <iostream>

KoalaDoctorList::KoalaDoctorList(KoalaDoctor * koala)
    : _koala { koala }
    , _next  { nullptr }
{
}

KoalaDoctorList::~KoalaDoctorList()
{

}

bool KoalaDoctorList::isEnd()
{
    if (!_next)
        return true;
    return false;
}

void KoalaDoctorList::append(KoalaDoctorList * list)
{
    if (!list)
        return;
    if (_next == nullptr)
        _next = list;
    else
        _next->append(list);
    list->setNext(nullptr);
}

KoalaDoctor * KoalaDoctorList::getFromName(const std::string name)
{
    if (!_koala)
        return nullptr;
    if (_koala->getName() == name)
        return _koala;
    if (!_next)
        return nullptr;
    return _next->getFromName(name);
}

KoalaDoctorList * KoalaDoctorList::remove(KoalaDoctorList * ptr)
{
    if (!ptr)
        return this;
    if (this == ptr)
    {
        const auto next = _next;
        _next = nullptr;
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

KoalaDoctorList * KoalaDoctorList::removeFromName(const std::string name)
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

void KoalaDoctorList::dumpName()
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

void KoalaDoctorList::dump()
{
    std::cout << "Doctors: ";
    dumpName();
    std::cout << std::endl;
}

KoalaDoctor * KoalaDoctorList::getContent()
{
    return _koala;
}

KoalaDoctorList * KoalaDoctorList::getNext()
{
    return _next;
}

std::string KoalaDoctorList::getKoalaName()
{
    if (!_koala)
        return std::string();
    return _koala->getName();
}

void KoalaDoctorList::setNext(KoalaDoctorList * ptr)
{
    if (this == ptr)
        return;
    _next = ptr;
}

void KoalaDoctorList::timeCheck()
{
    if (_koala)
        _koala->timeCheck();
}

void KoalaDoctorList::diagnose(SickKoalaList * sick)
{
    if (sick)
        getContent()->diagnose(sick->getContent());
}
