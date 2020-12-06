/*
** EPITECH PROJECT, 2020
** CInput.cpp
** File description:
** input class
*/

#include "CInput.hpp"

using namespace nts;

CInput::CInput(const std::string & name)
    : Component(name, {}, {1})
{
}

nts::Tristate CInput::compute(std::size_t pin)
{
    setLinksValues(_outputs);
    return _values[pin];
}

nts::Tristate CInput::computeOutput()
{
    return compute(1);
}

void CInput::dump() const
{
    std::cout << "CInput " << getName() << ", pin 1 : " << _values[1] << std::endl;
}

std::unique_ptr<IComponent> Factory::createInput(const std::string &value) const noexcept
{
    return std::unique_ptr<CInput>(new CInput(value));
}

void CInput::setInputValue(std::size_t, nts::Tristate value)
{
    setValue(1, value);
}

nts::ComponentType CInput::getComponentType() const
{
    return nts::ComponentType::INPUT;
}

void CInput::computeInput()
{
    compute(1);
}