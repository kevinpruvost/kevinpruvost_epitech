/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** AddValue
*/

#include "AddValue.hpp"

AddValue::AddValue(const char * const * argv, nts::Circuit & circuit)
    : _circuit { circuit }
    , av { argv }
{
}

AddValue::~AddValue()
{
}

bool AddValue::exec()
{
    std::regex find("\\s?(\\w+)=(\\d+)\\s?");
    std::cmatch match;

    for (int i = 2; av[i] != nullptr; ++i)
    {
        if (std::regex_search(av[i], match, find))
        {
            if (!_circuit.inputValue(
                    match.str(1),
                    (std::stoi(match.str(2))) ? nts::Tristate::TRUE
                                              : nts::Tristate::FALSE))
                return false;
        }
        else
        {
            throw EXCEPTION("Wrong input on command line.");
            return false;
        }
    }
    return true;
}

bool AddValue::parse()
{
    bool ret = true;

    try {
        ret = exec();
    } catch (const Exception & error) {
        std::cerr << error.what() << std::endl;
        ret = false;
    }

    return ret;
}