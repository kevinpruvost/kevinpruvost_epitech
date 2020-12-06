/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4081.hpp"

using namespace nts;

C4081::C4081(const std::string & name)
    : Component(name, {1, 2, 5, 6, 8, 9, 12, 13}, {3, 4, 10, 11})
{
}

nts::Tristate C4081::compute(std::size_t pin)
{
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    for (int i = 0; i < 2; ++i)
    {
        _values[3]  = Compute::And(_values[1], _values[2]);
        setLinksValues(_outputs);
        _values[4]  = Compute::And(_values[5], _values[6]);
        setLinksValues(_outputs);
        _values[10] = Compute::And(_values[8], _values[9]);
        setLinksValues(_outputs);
        _values[11] = Compute::And(_values[12], _values[13]);
    }

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C4081::dump() const
{
    std::cout << "Component " << _name << " with type C4081" << std::endl;
    for (int i = 0; i < 13; ++i)
        std::cout << "\t Pin " << i << " : " << _values[i] << std::endl;
}

void C4081::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 13; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4081(const std::string &value) const noexcept
{
    return std::unique_ptr<C4081>(new C4081(value));
}