/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4013.hpp"

using namespace nts;

C4013::C4013(const std::string & name)
    : Component(name, {3, 4, 5, 6, 8, 9, 10, 11}, {1, 2, 12, 13})
{
}

nts::Tristate C4013::compute(std::size_t pin)
{
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    if (_values[4] != UNDEFINED)
        _values[2] = (_values[4] == TRUE) ? TRUE : _values[2];
    if (_values[10] != UNDEFINED)
        _values[12] = (_values[10] == TRUE) ? TRUE : _values[12];
    if (_values[6] != UNDEFINED)
        _values[1] = (_values[6] == TRUE) ? TRUE : _values[1];
    if (_values[8] != UNDEFINED)
        _values[13] = (_values[8] == TRUE) ? TRUE : _values[13];

    if (_values[4] == FALSE && _values[6] == FALSE)
    {
        if (_values[3] == TRUE && clock1 == FALSE)
        {
            if (_values[5] != UNDEFINED)
            {
                _values[(_values[5] == TRUE) ? 1 : 2] = TRUE;
                _values[(_values[5] == TRUE) ? 2 : 1] = FALSE;
            }
        }
    }

    if (_values[10] == FALSE && _values[8] == FALSE)
    {
        if (_values[11] == TRUE && clock2 == FALSE)
        {
            if (_values[9] != UNDEFINED)
            {
                _values[(_values[9] == TRUE) ? 13 : 12] = TRUE;
                _values[(_values[9] == TRUE) ? 12 : 13] = FALSE;
            }
        }
    }

    if (_values[8] == TRUE && _values[10] == FALSE)
        _values[12] = FALSE;
    if (_values[10] == TRUE && _values[8] == FALSE)
        _values[13] = FALSE;
    if (_values[6] == TRUE && _values[4] == FALSE)
        _values[2] = FALSE;
    if (_values[4] == TRUE && _values[6] == FALSE)
        _values[1] = FALSE;

    _isComputed = true;
    setLinksValues(_outputs);
    clock1 = _values[3];
    clock2 = _values[11];
    return _values[pin];
}

void C4013::dump() const
{
    std::cout << "Component " << _name << " with type C4013" << std::endl;
}

void C4013::prepare()
{
    (clock1 == UNDEFINED) ? clock1 = _values[3] : 0;
    (clock2 == UNDEFINED) ? clock2 = _values[11] : 0;
    _isComputed = false;
    for (int i = 3; i <= 11; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4013(const std::string &value) const noexcept
{
    return std::unique_ptr<C4013>(new C4013(value));
}