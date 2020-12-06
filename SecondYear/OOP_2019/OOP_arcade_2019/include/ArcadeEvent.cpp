/*
** EPITECH PROJECT, 2020
** ArcadeEvent.cpp
** File description:
** arcade event
*/

#include "ArcadeEvent.hpp"

ArcadeEvent::ArcadeEvent(bool pressed, bool released, KeyValue keyValue,
                         int gameId, int displayId)
    : _pressed   { pressed   }
    , _released  { released  }
    , _keyValue  { keyValue  }
    , _gameId    { gameId    }
    , _displayId { displayId }
{
}

ArcadeEvent::~ArcadeEvent()
{
}