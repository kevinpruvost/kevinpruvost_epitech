/*
** EPITECH PROJECT, 2020
** ArcadeContent.hpp
** File description:
** aarcade
*/

#pragma once

// Project includes
#include "ArcadeEvent.hpp"

// C++ includes
#include <vector>

#define MAP_WIDTH  50
#define MAP_HEIGHT 30
#define SPRITE_WIDTH  (float)32
#define SPRITE_HEIGHT (float)32
#define WINDOW_X MAP_WIDTH  * SPRITE_WIDTH // 1600 = 50 * 32
#define WINDOW_Y MAP_HEIGHT * SPRITE_HEIGHT // 960 = 30 * 32

class ArcadeContent
{
public:
    ArcadeContent();
    ~ArcadeContent() = default;

public:
    std::vector<std::vector<char>> & map();
    ArcadeEvent & event();

private:
    std::vector<std::vector<char>> _map;
    ArcadeEvent _event;
};
