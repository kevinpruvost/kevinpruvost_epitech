/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

// Project includes
#include "IComponent.hpp"
#include "Compute.hpp"
#include "../Exception.hpp"

// C++ includes
#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace nts
{
class Circuit;

class Factory;

class Component;
class CInput;
class COutput;
class CTrue;
class CFalse;
class CClock;
class CChar;
class C2716;
class C4001;
class C4008;
class C4011;
class C4013;
class C4017;
class C4030;
class C4040;
class C4069;
class C4071;
class C4081;
class C4094;
class C4514;
class C4801;
} // !nts

class nts::Component : virtual public nts::IComponent
{
protected:
    Component(const std::string & name,
              const std::vector<std::size_t> & inputs = {},
              const std::vector<size_t> & outputs = {});
    Component(const nts::Component & comp);
    nts::Component & operator=(const nts::Component & comp);
    void setLink(std::size_t pin, nts::IComponent & other, std::size_t otherPin);
    virtual nts::Tristate compute(std::size_t pin = 1) = 0;
    virtual void dump() const = 0;
    virtual std::string display() const { return std::string(); }
    virtual void refreshClock() { };
    virtual void prepare() { };
    virtual nts::Tristate computeOutput() { return UNDEFINED; }
    const std::string & getName() const override { return _name; }
    nts::Tristate getValue(std::size_t pin) const override { return _values[pin]; }
    void setValue(std::size_t pin, nts::Tristate nb) override { _values[pin] = nb; }
    virtual void setInputValue(std::size_t, nts::Tristate) override { }
    bool getComputed() const override { return _isComputed; }
    void setComputed(bool computed) override { _isComputed = computed; }
    void setLinksValues(const std::vector<size_t> & tab = {});
    void computeInputs(const std::vector<size_t> & inputs = {});
    bool verifyLinksInputs() override;
    virtual void computeInput() {}

    bool operator==(IComponent & other) override { return _name == other.getName();};
    bool operator!=(IComponent & other) override { return !operator==(other); }

    const std::map<std::size_t, std::unique_ptr<std::vector<
        std::pair<nts::IComponent &, std::size_t>>>> & getLinks() const { return _links; }
    virtual nts::ComponentType getComponentType() const { return nts::ComponentType::COMPONENT; }

protected:
    bool _isComputed = false;
    std::map<std::size_t, std::unique_ptr<std::vector<
        std::pair<nts::IComponent &, std::size_t>>>> _links;
    std::string _name;
    std::vector<nts::Tristate> _values;
    std::vector<std::size_t> _inputs;
    std::vector<std::size_t> _outputs;
};

#endif // COMPONENT_HPP
