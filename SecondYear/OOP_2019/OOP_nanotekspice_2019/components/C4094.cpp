/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4094.hpp"

using namespace nts;

C4094::C4094(const std::string & name)
    : Component(name, {1, 2, 3, 15}, {4, 5, 6, 7, 14, 13, 12, 11, 10, 9})
{
    for (const auto & output : _outputs)
        _values[output] = FALSE;
}

void C4094::noOutputHigh()
{
    for (int i = 4; i <= 7; ++i)
        _values[i] = UNDEFINED;
    for (int i = 11; i <= 14; ++i)
        _values[i] = UNDEFINED;
    _values[9] = _values[12];
}

void C4094::noOutputLow()
{
    for (int i = 4; i <= 7; ++i)
        _values[i] = UNDEFINED;
    for (int i = 11; i <= 14; ++i)
        _values[i] = UNDEFINED;
    _values[10] = _values[12];
}

const std::vector<std::size_t> valuePins = {4, 5, 6, 7, 14, 13, 12, 11};

void C4094::outputClockHigh()
{
    if (_values[1] == TRUE)
    {
        for (auto ite = valuePins.rbegin(); (ite + 1) != valuePins.rend(); ++ite)
            _values[*ite] = _values[*(ite + 1)];
    }

    if (_values[1] == TRUE && _values[2] == TRUE)
        _values[4] = TRUE;
    else if (_values[1] == TRUE && _values[2] == FALSE)
        _values[4] = FALSE;

    _values[9] = _values[12];
    _values[11] = _values[12];
}

void C4094::outputClockLow()
{
    if (_values[1] == TRUE && _values[2] == TRUE)
        _values[10] = _values[12];
}

// 3 : Clock, 15 : Output, 1 : Strobe, 2 : Data 
nts::Tristate C4094::compute(std::size_t pin)
{
    static nts::Tristate clock = _values[3];

    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    //for (char i = 0; i < 2; ++i)
    //{
    if (clock == Compute::Invert(_values[3]))
    {
        if (_values[15] == FALSE && _values[3] == TRUE)
            noOutputHigh();
        else if (_values[15] == FALSE && _values[3] == FALSE)
            noOutputLow();
        else if (_values[15] == TRUE && _values[3] == TRUE)
            outputClockHigh();
        else if (_values[15] == TRUE && _values[3] == FALSE)
            outputClockLow();
        setLinksValues(_outputs);
    }
    //}

    _isComputed = true;
    setLinksValues(_outputs);
    clock = _values[3];
    return _values[pin];
}

void C4094::dump() const
{
    std::cout << "Component " << _name << " with type C4094" << std::endl;
}

void C4094::prepare()
{
    _isComputed = false;
    for (int i = 1; i <= 3; ++i)
        _values[i] = UNDEFINED;
    _values[15] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4094(const std::string &value) const noexcept
{
    return std::unique_ptr<C4094>(new C4094(value));
}