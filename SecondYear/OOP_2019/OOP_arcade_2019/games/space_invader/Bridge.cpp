/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Bridge
*/

#include "Bridge.hpp"

using namespace Spaceinvader;

Bridge::Bridge(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map)
: _pos (pos)
, _map (map)
{
}

Bridge::~Bridge()
{
}
