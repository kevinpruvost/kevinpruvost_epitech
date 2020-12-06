/*
** EPITECH PROJECT, 2020
** Compute.cpp
** File description:
** compute
*/

#include "Compute.hpp"

using namespace nts;

nts::Tristate Compute::Or(nts::Tristate in1, nts::Tristate in2)
{
    if (in1 == nts::Tristate::UNDEFINED && in2 == nts::Tristate::UNDEFINED)
        return nts::Tristate::UNDEFINED;
    if (in1 == nts::Tristate::TRUE || in2 == nts::Tristate::TRUE)
        return nts::Tristate::TRUE;
    if (in1 == nts::Tristate::UNDEFINED || in2 == nts::Tristate::UNDEFINED)
        return nts::Tristate::UNDEFINED;
    return nts::Tristate::FALSE;
}

nts::Tristate Compute::Nor(nts::Tristate in1, nts::Tristate in2)
{
    const auto res = Compute::Or(in1, in2);

    return Compute::Invert(res);
}

nts::Tristate Compute::Xor(nts::Tristate in1, nts::Tristate in2)
{
    if (in1 == nts::Tristate::UNDEFINED || in2 == nts::Tristate::UNDEFINED)
        return nts::Tristate::UNDEFINED;
    if (in1 == nts::Tristate::TRUE && in2 == nts::Tristate::TRUE)
        return nts::Tristate::FALSE;
    if (in1 == nts::Tristate::TRUE || in2 == nts::Tristate::TRUE)
        return nts::Tristate::TRUE;
    return nts::Tristate::FALSE;
}

nts::Tristate Compute::And(nts::Tristate in1, nts::Tristate in2)
{
    if (in1 == nts::Tristate::UNDEFINED && in2 == nts::Tristate::UNDEFINED)
        return nts::Tristate::UNDEFINED;
    if (in1 == nts::Tristate::FALSE || in2 == nts::Tristate::FALSE)
        return nts::Tristate::FALSE;
    if (in1 == nts::Tristate::UNDEFINED || in2 == nts::Tristate::UNDEFINED)
        return nts::Tristate::UNDEFINED;
    return nts::Tristate::TRUE;
}

nts::Tristate Compute::Nand(nts::Tristate in1, nts::Tristate in2)
{
    const auto res = Compute::And(in1, in2);

    return Compute::Invert(res);
}

nts::Tristate Compute::Sum(nts::Tristate in1, nts::Tristate in2)
{
    return Compute::Xor(in1, in2);
}

nts::Tristate Compute::Invert(nts::Tristate in)
{
    if (in == nts::Tristate::FALSE)
        return nts::Tristate::TRUE;
    else if (in == nts::Tristate::TRUE)
        return nts::Tristate::FALSE;
    return in;
}

nts::Tristate Compute::FullAdder(nts::Tristate in1, nts::Tristate in2, nts::Tristate cin)
{
    if (in1 == nts::Tristate::TRUE && in2 == nts::Tristate::TRUE)
        return nts::Tristate::TRUE;
    if (cin == nts::Tristate::TRUE && (in1 == nts::Tristate::TRUE
                                    || in2 == nts::Tristate::TRUE))
        return nts::Tristate::TRUE;
    if (cin == nts::Tristate::TRUE && in1 == nts::Tristate::FALSE
                                   && in2 == nts::Tristate::FALSE)
        return nts::Tristate::FALSE;
    if (in1 == nts::Tristate::FALSE || in2 == nts::Tristate::FALSE)
        return nts::Tristate::FALSE;
    return nts::Tristate::UNDEFINED;
}