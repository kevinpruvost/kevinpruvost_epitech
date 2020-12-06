/*
** EPITECH PROJECT, 2020
** IGameModule.hpp
** File description:
** game module interface
*/

#pragma once

// Project includes
#include "ArcadeEvent.hpp"

// C++ includes
#include <string>
#include <vector>

class IGameModule
{
public:
    virtual ~IGameModule() = default;

    virtual const std::string & getTextureFilepath() const = 0;

    virtual void update() = 0;
};