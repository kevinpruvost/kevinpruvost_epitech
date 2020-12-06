/*
** EPITECH PROJECT, 2020
** COutput.cpp
** File description:
** c output
*/

#include "COutput.hpp"

using namespace nts;

COutput::COutput(const std::string & name)
    : Component(name, {1}, {})
{
}

nts::Tristate COutput::compute(std::size_t)
{
    if (_isComputed)
        return UNDEFINED;
    computeInputs(_inputs);
    _isComputed = true;
    return _values[1];
}

nts::Tristate COutput::computeOutput()
{
    return compute(1);
}

void COutput::dump() const
{
    std::cout << "COutput " << getName() << ", pin 1 : " << _values[1] << std::endl;
}

std::string COutput::display() const
{
    std::stringstream sstream;

    if (_values[1] != UNDEFINED)
        sstream << getName() << "=" << _values[1] << std::endl;
    else
        sstream << getName() << "=U" << std::endl;
    return sstream.str();
}

void COutput::prepare()
{
    _values[1] = UNDEFINED;
    _isComputed = false;
}

std::unique_ptr<IComponent> Factory::createOutput(const std::string &value) const noexcept
{
    return std::unique_ptr<COutput>(new COutput(value));
}

nts::ComponentType COutput::getComponentType() const
{
    return nts::ComponentType::OUTPUT;
}