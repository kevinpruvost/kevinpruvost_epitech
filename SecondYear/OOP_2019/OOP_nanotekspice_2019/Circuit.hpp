/*
** Copyright 2020
**
** Made by Kevin Pruvost on 2020/2/3
** Mail kevin.pruvost@epitech.eu
**
** epitech.eu
*/

#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

// Project includes
#include "components/Factory.hpp"
#include "components/CAll.hpp"
#include "Exception.hpp"

// C++ includes
#include <vector>
#include <utility>
#include <map>

class nts::Circuit
{
public:
    Circuit();
    ~Circuit();

    bool addComponent(const std::string & type, const std::string & name);
    bool addLink(const std::string & name1, std::size_t pin1,
                 const std::string & name2, std::size_t pin2);

    void dump();
    void display();
    void refreshClocks();
    void prepareAll();
    void simulate();

    void sort();
    bool verifyLinks();

    bool inputValue(const std::string & name, nts::Tristate value);

    const std::vector<std::unique_ptr<nts::IComponent>> & getComponents() const;

public:
    std::vector<std::unique_ptr<nts::IComponent>> _components;

private:
    bool _sorted = false;
};

#endif // CIRCUIT_HPP
