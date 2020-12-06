/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "C2716.hpp"

using namespace nts;

C2716::C2716(const std::string & name)
    : Component(name, {}, {})
{
}

nts::Tristate C2716::compute(std::size_t pin)
{
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C2716::dump() const
{
    std::cout << "Component " << _name << " with type C2716" << std::endl;
}

void C2716::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 23; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create2716(const std::string &value) const noexcept
{
    return std::unique_ptr<C2716>(new C2716(value));
}