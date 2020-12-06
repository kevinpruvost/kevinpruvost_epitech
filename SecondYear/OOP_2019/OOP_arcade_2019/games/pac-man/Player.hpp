/*
** EPITECH PROJECT, 2020
** Player.hpp
** File description:
** player header
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <map>
#include <vector>
#include <chrono>

namespace Pacman
{
    class Player;
}

class Pacman::Player
{
public:
    Player(const std::pair<int, int> & pos, std::vector<std::vector<char>> & map);
    ~Player();

    std::pair<int, int> & getPos() { return _pos; }

    int moveLeft();
    int moveRight();
    int moveUp();
    int moveDown();

    void setLeft();
    void setRight();
    void setUp();
    void setDown();
    int getDirection();

    int moveForward();

    bool setSuper(bool state);
    bool getSuper();
    bool & dead();

    void update();

    void resetTime(std::chrono::milliseconds ms) { _startSuper += ms; }

private:
    int move(const std::pair<int, int> & pos);
    bool testMove(const std::pair<int, int> & pos);

private:
    std::pair<int, int> _pos;
    std::vector<std::vector<char>> & _map;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startSuper;

    bool _superMode = false;
    bool _isDead = false;
    int _direction = 0; // 0 1 2 3 : up down left right
};
