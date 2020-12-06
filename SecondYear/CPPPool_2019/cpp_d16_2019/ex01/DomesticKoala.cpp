/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/1/30
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "DomesticKoala.hpp"

DomesticKoala::DomesticKoala(KoalaAction & action)
    : _koala { action }
{
}

DomesticKoala::~DomesticKoala()
{
}

DomesticKoala::DomesticKoala(const DomesticKoala & koala)
    : _koala { koala._koala }
{
    _map = koala._map;
}

const std::vector<methodPointer_t> * DomesticKoala::getActions() const
{
    std::vector<methodPointer_t> * vec = new std::vector<methodPointer_t>;
    for (auto ite : _map)
        vec->push_back(ite.second);
    return vec;
}

void DomesticKoala::learnAction(unsigned char command, methodPointer_t action)
{
    _map.insert(std::pair<unsigned char, methodPointer_t>(command, action));
}

void DomesticKoala::unlearnAction(unsigned char command)
{
    _map.erase(command);
}

void DomesticKoala::doAction(unsigned char command, const std::string &param)
{
    const auto func = _map[command];
    if (func)
        (_koala.*func)(param);
}

void DomesticKoala::setKoalaAction(KoalaAction & oof)
{
    _koala = oof;
}
