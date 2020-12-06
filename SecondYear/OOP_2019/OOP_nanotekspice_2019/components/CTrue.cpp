/*
** EPITECH PROJECT, 2020
** CTrue.cpp
** File description:
** Ctrue
*/

#include "CTrue.hpp"

using namespace nts;

CTrue::CTrue(const std::string & name)
    : Component(name, {}, {1})
{
}

nts::Tristate CTrue::compute(std::size_t)
{
    _values[1] = nts::Tristate::TRUE;
    setLinksValues({1});
    return nts::Tristate::TRUE;
}

nts::Tristate CTrue::computeOutput()
{
    return compute(1);
}

void CTrue::dump() const
{
    std::cout << "Component " << getName() << " with type CTrue" << std::endl;
}

std::unique_ptr<IComponent> Factory::createTrue(const std::string &value) const noexcept
{
    return std::unique_ptr<CTrue>(new CTrue(value));
}

void CTrue::setInputValue(std::size_t, nts::Tristate value)
{
    setValue(1, value);
}

nts::ComponentType CTrue::getComponentType() const
{
    return nts::ComponentType::INPUT;
}

void CTrue::computeInput()
{
    compute(1);
}