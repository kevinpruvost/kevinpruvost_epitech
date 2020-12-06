/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Player
*/

#include "Player.hpp"

using namespace Spaceinvader;

Player::Player(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map)
: _pos (pos)
, _map (map)
, _shoot (std::pair<int, int>{-1, -1})
{
}

Player::~Player()
{
}

bool Player::testMove(const std::pair<int, int> & pos)
{
    if (_map[pos.first][pos.second] == ' ')
        return true;
    return false;
}

void Player::setLeft()
{
    if (testMove({_pos.first - 1, _pos.second}))
        _direction = 2;
}

int Player::move(const std::pair<int, int> & pos)
{
    if (pos.first < 0)
        const_cast<std::pair<int, int> &>(pos) = {_map.size() - 1, pos.second};
    if (pos.first >= (int)_map.size())
        const_cast<std::pair<int, int> &>(pos) = {0, pos.second};
    if (pos.second < 0)
        const_cast<std::pair<int, int> &>(pos) = {pos.first, _map[0].size() - 1};
    if (pos.second >= (int)_map[0].size())
        const_cast<std::pair<int, int> &>(pos) = {pos.first, 0};

    if (_map[pos.first][pos.second] == ' ')
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return 1;
    }
    else
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return 0;
    }
}


void Player::setRight()
{
    if (testMove({_pos.first + 1, _pos.second}))
        _direction = 3;
}

int Player::moveLeft()
{
    _direction = 0;
    return move({_pos.first - 1, _pos.second});
}

int Player::moveRight()
{
    _direction = 0;
    return move({_pos.first + 1, _pos.second});
}

int Player::shoot(std::vector<std::vector<char>> & map)
{
    if (_isShooting && _shoot != std::pair<int, int>{-1, -1}) {
        if (map[_shoot.first][_shoot.second -1] == 'M')
            return 1;
        if (map[_shoot.first][_shoot.second -1] == '"')
            return 2;
        if (map[_shoot.first][_shoot.second -1] == '#')
            return 3;
        if (map[_shoot.first][_shoot.second -1] == '|')
            return 3;
    } else {
        _shoot = std::pair<int, int>{_pos.first, _pos.second - 1};
        _isShooting = true;
        if (map[_shoot.first][_shoot.second -1] == 'M')
            return 1;
        if (map[_shoot.first][_shoot.second -1] == '"')
            return 2;
        if (map[_shoot.first][_shoot.second -1] == '#')
            return 3;
        if (map[_shoot.first][_shoot.second -1] == '|')
            return 3;
    }
    return 0;
}

int Player::moveForward(std::vector<std::vector<char>> & map)
{
    if (_direction == 2)
        return moveLeft();
    else if (_direction == 3)
        return moveRight();
    return 0;
}