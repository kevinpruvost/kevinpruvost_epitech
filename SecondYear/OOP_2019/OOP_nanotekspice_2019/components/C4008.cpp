/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4008.hpp"

using namespace nts;

C4008::C4008(const std::string & name)
    : Component(name, {1, 2, 3, 4, 5, 6, 7, 9, 15}, {10, 11, 12, 13, 14})
{
}

nts::Tristate C4008::compute(std::size_t pin)
{
    nts::Tristate c2 = nts::Tristate::UNDEFINED;
    nts::Tristate c3 = nts::Tristate::UNDEFINED;
    nts::Tristate c4 = nts::Tristate::UNDEFINED;

    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    _values[10] = Compute::Sum(_values[6], _values[7]);
    _values[10] = Compute::Sum(_values[10], _values[9]);
    c2 = Compute::FullAdder(_values[6], _values[7], _values[9]);
    _values[11] = Compute::Sum(_values[5], _values[4]);
    _values[11] = Compute::Sum(_values[11], c2);
    c3 = Compute::FullAdder(_values[5], _values[4], c2);
    _values[12] = Compute::Sum(_values[3], _values[2]);
    _values[12] = Compute::Sum(_values[12], c3);
    c4 = Compute::FullAdder(_values[3], _values[2], c3);
    _values[13] = Compute::Sum(_values[1], _values[15]);
    _values[13] = Compute::Sum(_values[13], c4);
    _values[14] = Compute::FullAdder(_values[1], _values[15], c4);

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C4008::dump() const
{
    std::cout << "Component " << _name << " with type C4008" << std::endl;
}

void C4008::prepare()
{
    _isComputed = false;
    for (size_t i = 0; i < 16; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4008(const std::string &value) const noexcept
{
    return std::unique_ptr<C4008>(new C4008(value));
}