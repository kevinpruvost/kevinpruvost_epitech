/*
** EPITECH PROJECT, 2020
** CFalse.cpp
** File description:
** cfalse
*/

#include "CFalse.hpp"

using namespace nts;

CFalse::CFalse(const std::string & name)
    : Component(name, {}, {1})
{
}

nts::Tristate CFalse::compute(std::size_t pin)
{
    _values[pin] = nts::Tristate::FALSE;
    setLinksValues(_outputs);
    return nts::Tristate::FALSE;
}

nts::Tristate CFalse::computeOutput()
{
    return compute(1);
}

void CFalse::dump() const
{
    std::cout << "Component " << _name << " with type CFalse" << std::endl;
}

std::unique_ptr<IComponent> Factory::createFalse(const std::string &value) const noexcept
{
    return std::unique_ptr<CFalse>(new CFalse(value));
}

void CFalse::setInputValue(std::size_t, nts::Tristate value)
{
    setValue(1, value);
}

nts::ComponentType CFalse::getComponentType() const
{
    return nts::ComponentType::INPUT;
}

void CFalse::computeInput()
{
    compute(1);
}