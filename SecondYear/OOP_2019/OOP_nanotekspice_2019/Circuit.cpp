/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "Circuit.hpp"

// C++ includes
#include <algorithm>

using namespace nts;

Factory factory;

const std::vector<const char *> chipsetsNames =
{
    "input", "clock", "true", "false", "output", "terminal",
    "2716", "4001", "4008", "4011", "4013", "4017", "4030",
    "4040", "4069", "4071", "4081", "4094", "4514", "4801"
};

Circuit::Circuit()
{
}

Circuit::~Circuit()
{
}

const std::vector<std::unique_ptr<nts::IComponent>> & Circuit::getComponents() const
{
    return _components;
}

struct chipCmp
{
    const std::string & key;
    chipCmp(const std::string & i): key(i) { }
 
    bool operator()(const char * i)
    {
        return (key == i);
    }
    bool operator()(const std::unique_ptr<IComponent> & i)
    {
        return (key == (*i).getName());
    }
};

bool Circuit::addComponent(const std::string & type, const std::string & name)
{
    const auto res = std::find_if(
        chipsetsNames.begin(), chipsetsNames.end(), chipCmp(type));

    if (res == chipsetsNames.end())
    {
        throw EXCEPTION("'" + type + "' chipset type is not existent.");
        return false;
    }
    if (std::find_if(_components.begin(), _components.end(), chipCmp(name))
     != _components.end())
    {
        throw EXCEPTION("'" + type + ": " + name +
            "' chipset is already in the components list.");
        return false;
    }
    _components.push_back(factory.createComponent(type, name));
    return true;
}

bool Circuit::addLink(const std::string & name1, std::size_t pin1,
                      const std::string & name2, std::size_t pin2)
{
    const auto comp1 = std::find_if(_components.begin(), _components.end(),
        chipCmp(name1));
    const auto comp2 = std::find_if(_components.begin(), _components.end(),
        chipCmp(name2));

    if (comp1 == _components.end())
        throw EXCEPTION("Component '" + name1 + "' does not exist.");
    if (comp2 == _components.end())
        throw EXCEPTION("Component '" + name2 + "' does not exist.");
    if (comp1 == _components.end() || comp2 == _components.end())
        return false;
    (*comp1)->setLink(pin1, *(*comp2), pin2);
    (*comp2)->setLink(pin2, *(*comp1), pin1);
    return true;
}

void Circuit::dump()
{
    for (const auto &comp : _components)
        comp->dump();
}

bool sortNames(std::pair<std::string, std::string> & n1,
               std::pair<std::string, std::string> & n2)
{
    if (n1.first < n1.second)
        return false;
    return true;
}

void Circuit::display()
{
    std::map<std::string, std::string> _strs;

    for (const auto & comp : _components)
        _strs.insert(std::pair<std::string, std::string>(comp->getName(), comp->display()));

    for (const auto & str : _strs)
        std::cout << str.second;
}

void Circuit::refreshClocks()
{
    for (const auto &comp : _components)
        comp->refreshClock();
}

void Circuit::prepareAll()
{
    for (const auto &comp : _components)
        comp->prepare();
}

bool Circuit::inputValue(const std::string & name, nts::Tristate value)
{
    const auto comp = std::find_if(_components.begin(), _components.end(),
        chipCmp(name));

    if (comp == _components.end())
    {
        throw EXCEPTION("Component '" + name + "' does not exist.");
        return false;
    }

    (*comp)->setInputValue(1, value);
    return true;
}

void Circuit::simulate()
{
    for (const auto & comp : _components)
        comp->computeInput();

    prepareAll();

    for (const auto & comp: _components)
    {
        comp->computeOutput();
    }

    for (const auto & comp: _components)
        comp->compute();

    refreshClocks();
}

bool Circuit::verifyLinks()
{
    for (const auto & comp: _components)
        if (!comp->verifyLinksInputs())
            return false;
    return true;
}