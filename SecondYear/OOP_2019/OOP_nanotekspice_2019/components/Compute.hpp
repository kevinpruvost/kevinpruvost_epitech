/*
** EPITECH PROJECT, 2020
** Compute.hpp
** File description:
** compute
*/

#pragma once

#include "IComponent.hpp"

namespace nts::Compute
{
    nts::Tristate And(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Nand(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Or(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Nor(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Xor(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Sum(nts::Tristate in1, nts::Tristate in2);
    nts::Tristate Invert(nts::Tristate in);
    nts::Tristate FullAdder(nts::Tristate in1, nts::Tristate in2, nts::Tristate cin);
} // !nts::Compute