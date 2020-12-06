/*
** EPITECH PROJECT, 2020
** AI.hpp
** File description:
** ai header
*/

#pragma once

// Project includes
#include "Exception.hpp"

// C++ includes
#include <algorithm>
#include <queue>
#include <map>
#include <iostream>
#include <vector>
#include <string.h>
#include <chrono>

// Projet defines
#define UPPAC       0
#define DOWNPAC     1
#define LEFTPAC     2
#define RIGHTPAC    3
#define MAP_WIDTH  50
#define MAP_HEIGHT 30

struct Cell
{
    int x;
    int y;
};

class queue_node
{
public:
    queue_node(Cell _pt, queue_node * _node)
        :pt(_pt)
        ,parent (_node) {};
    ~queue_node();
    Cell getCell() {return pt;};
    queue_node* getParent() {return parent;};
private:
    Cell pt;
    queue_node *parent;
};

namespace Pacman
{
    class AI;
}

class Pacman::AI
{
public:
    enum AiIdentities
    {
        BLINKY, // Red
        PINKY,  // Pink
        INKY,   // Cyan Blue
        CLYDE   // Orange
    };

public:
    AI(AiIdentities id, const std::pair<int, int> & pos, std::vector<std::vector<char>> & map);
    ~AI();

    const std::pair<int, int> & getPos() const { return _pos; }

    int moveLeft();
    int moveRight();
    int moveUp();
    int moveDown();
    int whichMove(std::pair<int, int> &);
    int whichMove(queue_node *);
    bool isAvailable(const std::pair<int, int> &);
    bool isValid(const std::pair<int, int> &);
    int runAway(queue_node *);
    std::pair<int, int> & getSegment(std::pair<int, int> &, const std::pair<int, int> &, int);
    int getCirclePlayer(std::pair<int, int> &);
    queue_node *pathfinding(std::pair<int, int> & );
    std::pair<int, int> & wherePlayerLooking(std::pair<int, int> &, int);
    bool closeEnough(std::pair<int, int> &);

    char getChar() const;
    void die();
    void resurrect();

    void setDead(bool die) { _isDead = die;};
    bool isDead() { return _isDead; }

    bool update(std::pair<int, int> & playerPos, int, const std::pair<int, int> &, bool supermode);

private:
    int move(const std::pair<int, int> & pos);

private:
    AiIdentities _id;
    bool _isDead = false;

    std::pair<int, int> _manipulate;
    std::pair<int, int> _pos;
    std::vector<std::vector<char>> & _map;
};