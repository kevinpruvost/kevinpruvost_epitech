/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4017.hpp"

using namespace nts;

// 13 : CP1, 14 : CP0, 15 : MR

C4017::C4017(const std::string & name)
    : Component(name, {13, 14, 15}, {3, 2, 4, 7, 10, 1, 5, 6, 9, 11, 12})
{
    for (int i = 1; i <= 11; ++i)
        _values[i] = FALSE;
    _values[3] = TRUE;
    _values[12] = TRUE;
}

void C4017::resetCount()
{
    for (int i = 1; i <= 11; ++i)
        _values[i] = FALSE;
    _values[3] = TRUE;
    _values[12] = TRUE;
}

void C4017::addCount()
{
    for (auto ite = _outputs.begin(); ite != _outputs.end(); ++ite)
    {
        if (_values[*ite] == TRUE && *ite != 12 && *ite != 11)
        {
            _values[*(ite + 1)] = TRUE;
            _values[*ite] = FALSE;
            if (*(ite + 1) == 1 || *(ite + 1) == 5 || *(ite + 1) == 6
             || *(ite + 1) == 9 || *(ite + 1) == 11)
                _values[12] = FALSE;
            else
                _values[12] = TRUE;
            return;
        }
        else if (_values[*ite] == TRUE && *ite == 11)
        {
            _values[11] = FALSE;
            _values[3] = TRUE;
            _values[12] = TRUE;
            return;
        }
    }
}

nts::Tristate C4017::compute(std::size_t pin)
{
    static nts::Tristate value14 = _values[14];
    static nts::Tristate value13 = Compute::Invert(_values[13]);

    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    if (_values[14] == UNDEFINED || _values[13] == UNDEFINED)
        return UNDEFINED;

    if (_values[14] == TRUE && _values[14] == Compute::Invert(value14)
     && _values[13] == FALSE)
        addCount();
    else if (_values[13] == FALSE && _values[13] == Compute::Invert(value13)
     && _values[14] == TRUE)
        addCount();

    if (_values[15] == TRUE)
        resetCount();

    _isComputed = true;
    value14 = _values[14];
    value13 = _values[13];
    setLinksValues(_outputs);
    return _values[pin];
}

// Dump, prepare, ... ----------------------------------------------------------

void C4017::dump() const
{
    std::cout << "Component " << _name << " with type C4017" << std::endl;
}

void C4017::prepare()
{
    _isComputed = false;
    for (int i = 13; i <= 15; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4017(const std::string &value) const noexcept
{
    return std::unique_ptr<C4017>(new C4017(value));
}