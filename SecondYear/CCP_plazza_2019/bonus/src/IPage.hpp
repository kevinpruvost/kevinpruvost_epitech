/*
** A Kevin Pruvost's project, May 2020
** IPage.hpp
** File description:
** page
*/

#pragma once

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ipc.hpp"
#include "SfmlIpc.hpp"

class IPage
{
public:
    virtual ~IPage() = default;

    virtual int exec() = 0;
    virtual int getPageChange() = 0;
    virtual void event(int &, bool &) = 0;

protected:
private:
};