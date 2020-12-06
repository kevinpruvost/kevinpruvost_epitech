/*
** EPITECH PROJECT, 2020
** AGameModule.hpp
** File description:
** game module
*/

#pragma once

// Project includes
#include "AModule.hpp"
#include "IGameModule.hpp"

class AGameModule : virtual public IGameModule, protected AModule
{
protected:
    AGameModule(ArcadeContent & arcadeContent, const std::string & path);
    virtual ~AGameModule() = default;

public:
    const std::string & getTextureFilepath() const override;
    void writeStringOnMap(int x, int y, const std::string & str);
    void writeCenteredStringOnMap(int x, int y, const std::string & str);

protected:
    std::string _textureFilePath;
};
