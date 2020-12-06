/*
** A Kevin Pruvost's project, May 2020
** SfmlPlazza.hpp
** File description:
** sfml plazza
*/

#pragma once

// Project includes
#include "Plazza.hpp"
#include "Ipc.hpp"

class SfmlPlazza : virtual public Plazza
{
public:
    SfmlPlazza(const char ** argv, Ipc & ipc);
    ~SfmlPlazza();

protected:
private:
    Ipc & _ipc;
};