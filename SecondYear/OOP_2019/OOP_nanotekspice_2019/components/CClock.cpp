/*
** EPITECH PROJECT, 2020
** CClock.cpp
** File description:
** clock
*/

#include "CClock.hpp"

using namespace nts;

CClock::CClock(const std::string & name)
    : Component(name, {}, {1})
{
    _values[1] = FALSE;
}

void CClock::refreshClock()
{
    _values[1] = Compute::Invert(_values[1]);
}

nts::Tristate CClock::compute(std::size_t pin)
{
    setLinksValues(_outputs);
    return _values[pin];
}

nts::Tristate CClock::computeOutput()
{
    return compute(1);
}

void CClock::dump() const
{
    std::cout << "CClock " << getName() << ", pin 1 : " << _values[1] << std::endl;
}

std::unique_ptr<IComponent> Factory::createClock(const std::string &value) const noexcept
{
    return std::unique_ptr<CClock>(new CClock(value));
}

void CClock::setInputValue(std::size_t, nts::Tristate value)
{
    setValue(1, value);
}

nts::ComponentType CClock::getComponentType() const
{
    return nts::ComponentType::INPUT;
}

void CClock::computeInput()
{
    compute(1);
}