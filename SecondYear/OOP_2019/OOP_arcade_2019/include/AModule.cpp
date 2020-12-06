/*
** EPITECH PROJECT, 2020
** AModule.cpp
** File description:
** amodule
*/

#include "AModule.hpp"

AModule::AModule(ArcadeContent & arcadeContent)
    : _arcadeContent { arcadeContent }
{
}

AModule::~AModule()
{
}

void AModule::setKey(ArcadeEvent::KeyValue key)
{
    _arcadeContent.event().getKeyValue() = key;
}

void AModule::changePrevGame()
{
    --_arcadeContent.event().getGameId();
    setKey(ArcadeEvent::KeyValue::CHANGE_GAME);
}

void AModule::changeNextGame()
{
    ++_arcadeContent.event().getGameId();
    setKey(ArcadeEvent::KeyValue::CHANGE_GAME);
}

void AModule::changeNextGraphical()
{
    ++_arcadeContent.event().getDisplayId();
    setKey(ArcadeEvent::KeyValue::CHANGE_GRAPH);
}

void AModule::changePrevGraphical()
{
    --_arcadeContent.event().getDisplayId();
    setKey(ArcadeEvent::KeyValue::CHANGE_GRAPH);
}

std::vector<std::vector<char>> & AModule::map()
{
    return _arcadeContent.map();
}

ArcadeEvent & AModule::event()
{
    return _arcadeContent.event();
}

ArcadeEvent::KeyValue AModule::getKey()
{
    return (ArcadeEvent::KeyValue)_arcadeContent.event().getKeyValue();
}

void AModule::clearMap()
{
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            map()[i][j] = 0;
        }
    }
}