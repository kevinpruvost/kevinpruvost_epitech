/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#include "CChar.hpp"

using namespace nts;

CChar::CChar(const std::string & name)
    : Component(name, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {})
{
}

void CChar::printChar() const
{
    if (_values[9] == FALSE)
        return;

    char c = 0;
    int mult = 1;

    for (int i = 1; i <= 8; ++i)
    {
        (_values[i] != UNDEFINED) ? (c += _values[i] * mult) : 0;
        mult *= 2;
    }
    std::cerr << c;
}

nts::Tristate CChar::compute(std::size_t pin)
{
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    printChar();

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void CChar::dump() const
{
    std::cout << "Component " << _name << " with type terminal" << std::endl;
}

void CChar::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 10; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::createChar(const std::string &value) const noexcept
{
    return std::unique_ptr<CChar>(new CChar(value));
}