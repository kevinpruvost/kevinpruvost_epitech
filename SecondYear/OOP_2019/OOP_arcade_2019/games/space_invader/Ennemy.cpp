/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Ennemy
*/

#include "Ennemy.hpp"

using namespace Spaceinvader;

Ennemy::Ennemy(const std::pair<int, int> & pos,  std::vector<std::vector<char>> & map)
: _pos (pos)
, _map (map)
, _direction (INVADERLEFT)
, isDead (false)
, _shoot (std::pair<int, int>{-1, -1})
{
    if (_pos.first == -1 || _pos.second == -1)
        throw EXCEPTION("AI not found in the map.");
}

Ennemy::~Ennemy()
{
}

int Ennemy::reduceHeight(std::vector<std::vector<char>> & map)
{
    if (_pos.second + 1 < (int)map.size())
        _pos.second += 1;
    else
        return 0;
    return 1;
}

int Ennemy::move(std::vector<std::vector<char>> & map)
{
    //std::pair<int, int> oldPos = _pos;
    if (_direction == INVADERLEFT && _pos.first - 1 >= 0 && map[_pos.first - 1][_pos.second] != '#')
        _pos.first -= 1;
    else if (_direction == INVADERRIGHT && _pos.first + 1 < (int)map[0].size() && map[_pos.first + 1][_pos.second] != '#')
        _pos.first += 1;
    else
        return 0;
    /*if (!isDead) {
        map[oldPos.first][oldPos.second] = ' ';
        map[_pos.first][_pos.second] = 'M';
    }*/
    return 1;
}

bool Ennemy::canIShoot(std::vector<std::vector<char>> & map)
{
    for (size_t i = 1; _pos.second + i < map.size(); ++i) {
        if (map[_pos.first][_pos.second + i] == 'M')
            return false;
    }
    int res = rand() % (64);
    if (res == 2)
        return true;
    return false;
}

int Ennemy::shoot(std::vector<std::vector<char>> & map)
{
    if (_pos.second >= MAP_HEIGHT - 2)
        return 1;
    if (!_isShooting && !canIShoot(map))
        return -1;
    if (_isShooting) {
        if (map[_shoot.first][_shoot.second + 1] == 'P')
            return 1;
        if (map[_shoot.first][_shoot.second + 1] == '"')
            return 2;
        if (map[_shoot.first][_shoot.second + 1] == '#')
            return 3;
        if (map[_shoot.first][_shoot.second + 1] == '|')
            return 3;
    } else {
        _shoot = std::pair<int, int>{_pos.first, _pos.second + 1};
        _isShooting = true;
        if (map[_shoot.first][_shoot.second + 1] == 'P')
            return 1;
        if (map[_shoot.first][_shoot.second + 1] == '"')
            return 2;
        if (map[_shoot.first][_shoot.second + 1] == '#')
            return 3;
        if (map[_shoot.first][_shoot.second + 1] == '|')
            return 3;
    }
    return 0;
}

int Ennemy::update(std::vector<std::vector<char>> & map, int & direction)
{
    if (isDead)
        return 0;
    _direction = direction;
    return move(map);
}