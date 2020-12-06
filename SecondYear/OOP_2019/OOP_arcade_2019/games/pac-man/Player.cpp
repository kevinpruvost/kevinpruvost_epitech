/*
** EPITECH PROJECT, 2020
** Player.cpp
** File description:
** player source
*/

#include "Player.hpp"

// C++ includes
#include <iostream>

using namespace Pacman;

Player::Player(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map)
    : _pos { pos }
    , _map { map }
{
    if (_pos.first == -1 || _pos.second == -1)
        throw EXCEPTION("Player not found in the map.");
}

Player::~Player()
{
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

    if (_map[pos.first][pos.second] == 'O')
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return 10;
    }
    else if (_map[pos.first][pos.second] == '+')
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        setSuper(true);
        return 50;
    }
    else if (_map[pos.first][pos.second] == '#')
        return 0;
    else if ((_map[pos.first][pos.second] == 'A'
          || _map[pos.first][pos.second] == 'B'
          || _map[pos.first][pos.second] == 'C'
          || _map[pos.first][pos.second] == 'D') && !_superMode)
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return -1;
    }
    else if (_map[pos.first][pos.second] == 'F' && _superMode)
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return 100;
    }
    else
    {
        _pos.first = pos.first;
        _pos.second = pos.second;
        return 0;
    }
}

void Player::setLeft()
{
    if (testMove({_pos.first - 1, _pos.second}))
        _direction = 2;
}

void Player::setRight()
{
    if (testMove({_pos.first + 1, _pos.second}))
        _direction = 3;
}

void Player::setUp()
{
    if (testMove({_pos.first, _pos.second - 1}))
        _direction = 0;
}

void Player::setDown()
{
    if (testMove({_pos.first, _pos.second + 1}))
        _direction = 1;
}

bool Player::testMove(const std::pair<int, int> & pos)
{
    if (pos.first < 0)
        const_cast<std::pair<int, int> &>(pos) = {_map.size() - 1, pos.second};
    if (pos.first >= (int)_map.size())
        const_cast<std::pair<int, int> &>(pos) = {0, pos.second};
    if (pos.second < 0)
        const_cast<std::pair<int, int> &>(pos) = {pos.first, _map[0].size() - 1};
    if (pos.second >= (int)_map[0].size())
        const_cast<std::pair<int, int> &>(pos) = {pos.first, 0};

    if (_map[pos.first][pos.second] == 'O')
        return true;
    else if (_map[pos.first][pos.second] == '+')
        return true;
    else if (_map[pos.first][pos.second] == '#')
        return false;
    else if ((_map[pos.first][pos.second] == 'A'
          || _map[pos.first][pos.second] == 'B'
          || _map[pos.first][pos.second] == 'C'
          || _map[pos.first][pos.second] == 'D') && !_superMode)
        return true;
    else if (_map[pos.first][pos.second] == 'F' && _superMode)
        return true;
    else
        return true;
}

int Player::getDirection()
{
    return _direction;
}

int Player::moveLeft()
{
    return move({_pos.first - 1, _pos.second});
}

int Player::moveRight()
{
    return move({_pos.first + 1, _pos.second});
}

int Player::moveUp()
{
    return move({_pos.first, _pos.second - 1});
}

int Player::moveDown()
{
    return move({_pos.first, _pos.second + 1});
}

int Player::moveForward()
{
    if (_direction == 0)
        return moveUp();
    else if (_direction == 1)
        return moveDown();
    else if (_direction == 2)
        return moveLeft();
    else if (_direction == 3)
        return moveRight();
    return 0;
}

void Player::update()
{
    if (_superMode)
    {
        auto end = std::chrono::system_clock::now();
        int sec = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end - _startSuper).count();
        if (sec >= 20 * 1000)
        {
            _superMode = false;
        }
    }
}

bool Player::getSuper()
{
    return _superMode;
}

bool Player::setSuper(bool state)
{
    if (state)
        _startSuper = std::chrono::system_clock::now();
    _superMode = state;
    return state;
}

bool & Player::dead()
{
    return _isDead;
}