/*
** EPITECH PROJECT, 2020
** ArcadeContent.cpp
** File description:
** arcade
*/

#include "ArcadeContent.hpp"

ArcadeContent::ArcadeContent()
{
    _map.resize(MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; ++i)
        _map[i].resize(MAP_HEIGHT, 0);
}

std::vector<std::vector<char>> & ArcadeContent::map() { return _map; }

ArcadeEvent & ArcadeContent::event() { return _event; }