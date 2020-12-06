/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4069.hpp"

using namespace nts;

C4069::C4069(const std::string & name)
    : Component(name, {1, 3, 5, 9, 11, 13}, {2, 4, 6, 8, 10, 12})
{
}

nts::Tristate C4069::compute(std::size_t pin)
{
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    for (char i = 0; i < 2; ++i)
    {
        _values[2] = Compute::Invert(_values[1]);
        setLinksValues(_outputs);
        _values[4] = Compute::Invert(_values[3]);
        setLinksValues(_outputs);
        _values[6] = Compute::Invert(_values[5]);
        setLinksValues(_outputs);
        _values[8] = Compute::Invert(_values[9]);
        setLinksValues(_outputs);
        _values[10] = Compute::Invert(_values[11]);
        setLinksValues(_outputs);
        _values[12] = Compute::Invert(_values[13]);
        setLinksValues(_outputs);
    }

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C4069::dump() const
{
    std::cout << "Component " << _name << " with type C4069" << std::endl;
}

void C4069::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 13; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4069(const std::string &value) const noexcept
{
    return std::unique_ptr<C4069>(new C4069(value));
}