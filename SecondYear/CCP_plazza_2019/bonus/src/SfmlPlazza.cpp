/*
** A Kevin Pruvost's project, May 2020
** SfmlPlazza.cpp
** File description:
** sfml plazza
*/

#include "SfmlPlazza.hpp"

SfmlPlazza::SfmlPlazza(const char ** argv, Ipc & ipc)
    : Plazza(argv)
    , _ipc { ipc }
{
}

SfmlPlazza::~SfmlPlazza()
{
}