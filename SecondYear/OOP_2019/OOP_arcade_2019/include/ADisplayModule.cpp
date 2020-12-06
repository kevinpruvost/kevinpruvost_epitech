/*
** EPITECH PROJECT, 2020
** ADisplayModule.cpp
** File description:
** display module
*/

#include "ADisplayModule.hpp"

ADisplayModule::ADisplayModule(ArcadeContent & arcadeContent,
                             const std::string & name)
    : AModule(arcadeContent)
    , _name { name }
{
}

void ADisplayModule::setTexture(const std::string & fileName)
{
    _spriteInfos.clear();
    try {
        _spriteInfos = loadSpriteDataFromFile(fileName);
    } catch(const std::exception & e) {
        throw Exception(e.what());
        return;
    }
    _spriteDirectory = getSpriteDirectory(fileName);
    setExtraTexture();
}