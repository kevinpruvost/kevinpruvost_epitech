/*
** EPITECH PROJECT, 2020
** ADisplayModule.hpp
** File description:
** display module
*/

#pragma once

// C++ includes
#include <iostream>

// Project includes
#include "AModule.hpp"
#include "IDisplayModule.hpp"
#include "SpriteData.hpp"

class ADisplayModule : virtual public IDisplayModule, protected AModule
{
protected:
    ADisplayModule(ArcadeContent & arcadeContent, const std::string & name);
    virtual ~ADisplayModule() = default;

    void setTexture(const std::string & fileName) override;

    std::vector<std::vector<char>> & arcadeMap() { return _arcadeContent.map(); }
    ArcadeEvent & arcadeEvent() { return _arcadeContent.event(); }

    virtual void setExtraTexture() = 0;

protected:
    const std::string _name;
    std::string _spriteDirectory;

    std::map<char, SpriteData> _spriteInfos;
};