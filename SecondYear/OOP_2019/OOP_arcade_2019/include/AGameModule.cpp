/*
** EPITECH PROJECT, 2020
** AGameModule.hpp
** File description:
** game module
*/

#include "AGameModule.hpp"

// C includes
#include <cstring>

AGameModule::AGameModule(ArcadeContent & arcadeContent, const std::string & path)
    : AModule(arcadeContent)
    , _textureFilePath { "games/" + path }
{
}

const std::string & AGameModule::getTextureFilepath() const
{
    return _textureFilePath;
}

void AGameModule::writeStringOnMap(int x, int y, const std::string & str)
{
    for (const auto & c : str)
        map()[x++][y] = c;
}

void AGameModule::writeCenteredStringOnMap(int x, int y, const std::string & str)
{
    writeStringOnMap(x - (strlen(str.c_str()) / 2), y, str);
}