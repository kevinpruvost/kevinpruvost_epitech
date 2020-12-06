/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4801.hpp"

using namespace nts;

C4801::C4801(const std::string & name)
    : Component(name, {}, {})
{
}

nts::Tristate C4801::compute(std::size_t pin)
{
    std::cout << "oui" << std::endl;
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C4801::dump() const
{
    std::cout << "Component " << _name << " with type C4801" << std::endl;
}

void C4801::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 23; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4801(const std::string &value) const noexcept
{
    return std::unique_ptr<C4801>(new C4801(value));
}