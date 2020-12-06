/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4040.hpp"

using namespace nts;

C4040::C4040(const std::string & name)
    : Component(name, {10, 11}, {9, 7, 6, 5, 3, 2, 4, 13, 12, 14, 15, 1})
{
    for (const auto i : _outputs)
        _values[i] = FALSE;
}

size_t C4040::readCount() const
{
    size_t nb = 0;
    size_t mult = 1;

    for (auto ite = _outputs.begin(); ite != _outputs.end(); ++ite, mult *= 2)
    {
        if (_values[*ite] == TRUE)
            nb += mult;
    }
    return nb;
}

void C4040::resetCount()
{
    for (const auto i : _outputs)
        _values[i] = FALSE;
}

void C4040::addCount()
{
    setCount(readCount() + 1);
}

void C4040::setCount(size_t count)
{
    resetCount();

    if (count > 4095)
        count = 0;

    size_t mult = 2048;
    for (auto it = _outputs.rbegin(); it != _outputs.rend() && count > 0; ++it)
    {
        if (count >= mult)
        {
            _values[*it] = TRUE;
            count -= mult;
        }
        mult /= 2;
    }
}

nts::Tristate C4040::compute(std::size_t pin)
{
    static nts::Tristate clock = _values[10];

    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    if (_values[10] == UNDEFINED)
        return UNDEFINED;

    if (clock == TRUE && _values[10] == FALSE)
        addCount();
    setLinksValues(_outputs);

    if (_values[11] == TRUE)
        resetCount();
    setLinksValues(_outputs);

    _isComputed = true;
    clock = _values[10];
    setLinksValues(_outputs);
    return _values[pin];
}

void C4040::dump() const
{
    std::cout << "Component " << _name << " with type C4040" << std::endl;
}

void C4040::prepare()
{
    _isComputed = false;
    for (int i = 10; i <= 11; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4040(const std::string &value) const noexcept
{
    return std::unique_ptr<C4040>(new C4040(value));
}