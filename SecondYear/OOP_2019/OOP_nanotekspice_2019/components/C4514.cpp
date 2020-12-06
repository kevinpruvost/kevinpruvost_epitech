/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/
#include "C4514.hpp"

using namespace nts;

C4514::C4514(const std::string & name)
    : Component(name, {2, 3, 21, 22},
                {4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20})
{
}

const std::vector<size_t> ids = {11, 9, 10, 8, 7, 6, 5, 4, 18, 17, 20, 19,
                                 14, 13, 16, 15};

nts::Tristate C4514::compute(std::size_t pin)
{
    if (_values[2]  == UNDEFINED || _values[3]  == UNDEFINED
     || _values[21] == UNDEFINED || _values[22] == UNDEFINED)
        return UNDEFINED;
    if (_isComputed)
        return UNDEFINED;

    computeInputs(_inputs);

    for (char i = 0; i < 2; ++i)
    {
        const size_t index = 1 * _values[2] + 2 * _values[3] + 4 * _values[21]
                           + 8 * _values[22];
        for (size_t i = 4; i <= 20; ++i)
        {
            if (i != 2 && i != 3 && i != 12)
                _values[i] = Tristate::FALSE;
            setLinksValues(_outputs);
        }
        if (_values[23] != TRUE)
            _values[ids[index]] = Tristate::TRUE;
    }

    _isComputed = true;
    setLinksValues(_outputs);
    return _values[pin];
}

void C4514::dump() const
{
    std::cout << "Component " << _name << " with type C4514" << std::endl;
}

void C4514::prepare()
{
    _isComputed = false;
    for (size_t i = 0; i < 24; ++i)
        _values[i] = UNDEFINED;
}

std::unique_ptr<IComponent> Factory::create4514(const std::string &value) const noexcept
{
    return std::unique_ptr<C4514>(new C4514(value));
}