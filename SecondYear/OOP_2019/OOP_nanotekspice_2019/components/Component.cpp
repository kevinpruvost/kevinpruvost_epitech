/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include <algorithm>

#include "Component.hpp"

using namespace nts;

Component::Component(const std::string & name,
                     const std::vector<std::size_t> & inputs,
                     const std::vector<size_t> & outputs)
    : _name { name }
    , _inputs { inputs }
    , _outputs { outputs }
{
    for (unsigned char i = 0; i < 255; ++i)
    {
        _values.push_back(nts::Tristate::UNDEFINED);

        auto map = new std::vector<std::pair<nts::IComponent &, std::size_t>>();
        _links.insert(std::pair<std::size_t,
            std::unique_ptr<std::vector<std::pair<nts::IComponent &, std::size_t>>>>(i, map));
    }
}

Component::Component(const nts::Component & name)
    : _name { name.getName() }
{
}

Component & Component::operator=(const nts::Component & comp)
{
    _name = comp.getName();
    return *this;
}

void Component::setLink(std::size_t pin, nts::IComponent & other,
                        std::size_t otherPin)
{
    auto & newMap = _links[pin];

    newMap->push_back(std::pair<nts::IComponent &, std::size_t>(other, otherPin));
}

void Component::setLinksValues(const std::vector<size_t> & tab)
{
    if (tab.empty())
        return;

    // link.first : [pin0], spair : [component1, pin1]
    for (auto & link : _links)
    {
        auto & spair = link.second;
        for (auto & spart : *spair)
        {
            if (std::find(tab.begin(), tab.end(), link.first) != tab.end())
            {
                spart.first.setValue(spart.second, _values[link.first]);
                //std::cout << "Setting " << spart.first.getName() << " " << spart.second 
                //<< " = " << spart.first.getValue(spart.second) << std::endl;
            }
        }
    }
}

void Component::computeInputs(const std::vector<size_t> & tab)
{
    if (tab.empty())
        return;

    IComponent & me = *this;

    // link.first : [pin0], spair : [component1, pin1]
    //std::cout << "Computing " << _name << " inputs" << std::endl;
    for (auto & link : _links)
    {
        auto & spair = link.second;
        for (auto & spart : *spair)
        {
            if (std::find(tab.begin(), tab.end(), link.first) != tab.end())
            {
                //std::cout << spair.first.getName() << std::endl;
                if (spart.first != me)
                    spart.first.compute();
            }
        }
    }
    //std::cout << std::endl;
}

bool Component::verifyLinksInputs()
{
    const std::vector<size_t> & tab = _inputs;
    std::vector<size_t> inputsOnce;

    for (auto & link : _links)
    {
        if (std::find(tab.begin(), tab.end(), link.first) != tab.end())
        {
            if (std::find(inputsOnce.begin(), inputsOnce.end(), link.first) 
                != inputsOnce.end())
            {
                throw EXCEPTION("Multiple links on input pin "
                    + std::to_string(link.first) + " on " + _name);
                return false;
            }
            inputsOnce.push_back(link.first);
        }
    }
    return true;
}