/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/24
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Squad.hpp"

Squad::Squad()
{
}

Squad::Squad(ISquad & otherSquad)
{
    for (int i = 0; i < otherSquad.getCount(); ++i)
    {
        auto marine = otherSquad.getUnit(i);
        auto newMarine = marine->clone();
        push(newMarine);
    }
}

Squad::~Squad()
{
    for (const auto part : _marines)
        delete part;
}

Squad & Squad::operator=(ISquad & otherSquad)
{
    for (auto ite = _marines.begin(); ite != _marines.end(); ++ite)
    {
        delete *ite;
        _marines.erase(ite);
    }

    for (int i = 0; i < otherSquad.getCount(); ++i)
    {
        auto marine = otherSquad.getUnit(i);
        auto newMarine = marine->clone();
        push(newMarine);
    }
    return *this;
}

int Squad::getCount() const
{
    return _marines.size();
}

int Squad::push(ISpaceMarine * marine)
{
    if (!marine)
        return _marines.size();
    _marines.push_back(marine);
    return _marines.size();
}

ISpaceMarine * Squad::getUnit(int id)
{
    if ((int)_marines.size() <= id || id < 0)
        return nullptr;
    return _marines.at(id);
}
