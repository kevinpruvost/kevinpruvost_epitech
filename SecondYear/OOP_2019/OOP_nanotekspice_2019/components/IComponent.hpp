/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef ICOMPONENT_HPP
#define ICOMPONENT_HPP

// C++ includes
#include <cstring>
#include <memory>
#include <vector>
#include <memory>
#include <map>

namespace nts
{
    enum Tristate
    {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };

    enum ComponentType
    {
        INPUT,
        COMPONENT,
        OUTPUT
    };

    class IComponent
    {
    public:
        virtual ~IComponent() = default;

    public:
        virtual nts::Tristate compute(std::size_t pin = 1) = 0;
        virtual nts::Tristate computeOutput() = 0;
        virtual void setLink(std::size_t pin, nts::IComponent &other,
                             std::size_t otherPin) = 0;
        virtual const std::map<std::size_t, std::unique_ptr<std::vector<
        std::pair<nts::IComponent &, std::size_t>>>> & getLinks() const = 0;
        virtual nts::ComponentType getComponentType() const = 0;
        virtual void dump() const = 0;
        virtual std::string display() const = 0;
        virtual void refreshClock() = 0;
        virtual void prepare() = 0;
        virtual const std::string & getName() const = 0;
        virtual nts::Tristate getValue(std::size_t pin) const = 0;
        virtual void setValue(std::size_t pin, nts::Tristate nb) = 0;
        virtual void setInputValue(std::size_t pin, nts::Tristate nb) = 0;
        virtual bool getComputed() const = 0;
        virtual void setComputed(bool computed) = 0;
        virtual bool verifyLinksInputs() = 0;
        virtual bool operator==(IComponent & other) = 0;
        virtual bool operator!=(IComponent & other) = 0;
        virtual void computeInput() = 0;
    };
}

#endif // ICOMPONENT_HPP
