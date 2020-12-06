/*
** EPITECH PROJECT, 2020
** AI.cpp
** File description:
** ai source
*/

#include "AI.hpp"

// C++ includes
#include <random>

using namespace Pacman;

AI::AI(AiIdentities id, const std::pair<int, int> & pos, std::vector<std::vector<char>> & map)
    : _id { id }
    , _pos { pos }
    , _map { map }
{
    if (_pos.first == -1 || _pos.second == -1)
        throw EXCEPTION("AI not found in the map.");
}

AI::~AI()
{
}

char AI::getChar() const
{
    if (_isDead)
        return 'E';
    if (_id == AiIdentities::BLINKY)
        return 'A';
    if (_id == AiIdentities::PINKY)
        return 'B';
    if (_id == AiIdentities::INKY)
        return 'C';
    if (_id == AiIdentities::CLYDE)
        return 'D';
    return 0;
}

void AI::die()
{
    _isDead = true;
}

void AI::resurrect()
{
    _isDead = false;
}

int AI::move(const std::pair<int, int> & pos)
{
    if (pos.first < 0)
        const_cast<std::pair<int, int> &>(pos) = {_map.size() - 1, pos.second};
    if (pos.first >= (int)_map.size())
        const_cast<std::pair<int, int> &>(pos) = {0, pos.second};
    if (pos.second < 0)
        const_cast<std::pair<int, int> &>(pos) = {pos.first, _map[0].size() - 1};
    if (pos.second >= (int)_map[0].size())
        const_cast<std::pair<int, int> &>(pos) = {pos.first, 0};

    if (_map[pos.first][pos.second] == '#' || _map[pos.first][pos.second] == 'E')
        return 0;
    else if ((_map[pos.first][pos.second] == 'A'
          || _map[pos.first][pos.second] == 'B'
          || _map[pos.first][pos.second] == 'C'
          || _map[pos.first][pos.second] == 'D'))
    {
        return 0;
    }
    else if (_map[pos.first][pos.second] == 'P')
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

int absolutvalue(int value)
{
    value = (value < 0) ? value * -1 : value;
    return value;
}

int AI::moveLeft()
{
    return move({_pos.first - 1, _pos.second});
}

int AI::moveRight()
{
    return move({_pos.first + 1, _pos.second});
}

int AI::moveUp()
{
    return move({_pos.first, _pos.second - 1});
}

int AI::moveDown()
{
    return move({_pos.first, _pos.second + 1});
}

int AI::whichMove(queue_node * pos)
{
    for (;pos->getParent() != nullptr && pos->getParent()->getParent() != nullptr;) {
        pos = pos->getParent();
    }
    if (_pos.first+1 == pos->getCell().x)
        moveRight();
    else if (_pos.first-1 == pos->getCell().x)
        moveLeft();
    else if (_pos.second+1 == pos->getCell().y)
        moveDown();
    else if (_pos.second-1 == pos->getCell().y)
        moveUp();
    return 0;
}

bool AI::isValid(const std::pair<int, int> & pos)
{
    return ((pos.first >= 0) && (pos.first < (int)_map.size()) && (pos.second >= 0) && (pos.second < (int)_map[0].size())); 
}

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

//BFS algorithm

queue_node* AI::pathfinding(std::pair<int, int> & player)
{
    bool visited[_map.size()+1][_map[0].size()+1];
    memset(visited, false, sizeof(visited));

    visited[_pos.first][_pos.second] = true;

    std::queue<queue_node *> q;
    q.push(new queue_node({{_pos.first, _pos.second}, {nullptr}}));

    while (!q.empty()) {
        queue_node *P = new queue_node(q.front()->getCell(), q.front()->getParent());
        if (P->getCell().x == player.first && P->getCell().y == player.second)
            return P;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int row = P->getCell().x + rowNum[i];
            int col = P->getCell().y + colNum[i];
            if (isValid(std::pair<int, int>{row, col}) && !visited[row][col] && _map[row][col] != '#') { 
                visited[row][col] = true;
                queue_node *Adjcell = new queue_node({row, col}, P);
                q.push(Adjcell);
            }
        }
    }
    return nullptr;
}

std::pair<int, int> & AI::getSegment(std::pair<int, int> & PlayerPos, const std::pair<int, int> & RedAIPosition, int Direction)
{
    std::pair<int, int> look = AI::wherePlayerLooking(PlayerPos, Direction);
    int coefX = 0;
    int coefY = 0;

    bool Switch = false;

    if (RedAIPosition.first > look.first)
        coefX = RedAIPosition.first - look.first;
    else if (look.first > RedAIPosition.first)
        coefX = look.first - RedAIPosition.first;
    if (RedAIPosition.second > look.second)
        coefY = RedAIPosition.second - look.second;
    else if (look.second > RedAIPosition.second)
        coefY = look.second - RedAIPosition.second;

    int tempX = 0;
    int tempY = 0;

    while (look.first + coefX >= 0 && look.first + coefX < (int)_map.size() && look.second + coefY >= 0 && look.second + coefY < (int)_map[0].size() && this->_map[look.first + coefX][look.second + coefY] == '#') {
        if (Switch == false) {
            tempX += 1;
            tempY += 1;
        } else {
            tempX -= 1;
            tempY -= 1;
        }
        if (tempX > (int)_map.size() || tempY > (int)_map[0].size()) {
            tempX = coefX;
            tempY = coefY;
            Switch = true;
        }
        if (tempX <= look.first || tempY <= look.second) {
            tempX = 0;
            tempY = 0;
            break;
        }
    }
    _manipulate = std::pair<int, int>{look.first + tempX, look.second + tempY};
    return _manipulate;
}

bool AI::isAvailable(const std::pair<int, int> & pos)
{
    return ((pos.first >= 0 && pos.first < (int)_map.size()) && (pos.second >= 0 && pos.second < (int)_map[0].size()) && (_map[pos.first][pos.second] != '#'));
}

std::pair<int, int> & AI::wherePlayerLooking(std::pair<int, int> & PosPlayer, int Direction)
{
    int x = PosPlayer.first;
    int y = PosPlayer.second;
    int diff = 0;
    int posdiff = 8;

    if (_id == PINKY)
        posdiff = 20;

    if ((PosPlayer.first <= _pos.first + posdiff || _pos.first - posdiff >= PosPlayer.first) && PosPlayer.second == _pos.second)
        return PosPlayer;
    if ((PosPlayer.second <= _pos.second + posdiff || _pos.second - posdiff >= PosPlayer.second) && PosPlayer.first == _pos.first)
        return PosPlayer;

    switch (Direction) {
    case LEFTPAC:
        for (diff = x; isAvailable(std::pair<int, int>{x - 1, y}) && diff - x != posdiff; --x);
        if (diff - x != posdiff) {
            for (diff = y; isAvailable(std::pair<int, int>{x, y - 1}) && diff - y != posdiff; --y);
            if (diff == y)
                for (diff = y; isAvailable(std::pair<int, int>{x, y + 1}) && y - diff != posdiff; ++y);
        }
        break;
    case RIGHTPAC:
        for (diff = x; isAvailable(std::pair<int, int>{x + 1, y}) && x - diff != posdiff; ++x);
        if (x - diff != posdiff) {
            for (diff = y; isAvailable(std::pair<int, int>{x, y - 1}) && diff - y != posdiff; --y);
            if (diff == y)
                for (diff = y; isAvailable(std::pair<int, int>{x, y + 1}) && y - diff != posdiff; ++y);
        }
        break;
    case UPPAC:
        for (diff = y; isAvailable(std::pair<int, int>{x, y - 1}) && diff - y != posdiff; --y);
        if (diff - y != posdiff) {
            for (diff = x; isAvailable(std::pair<int, int>{x - 1, y}) && diff - x != posdiff; --x);
            if (diff == x)
                for (diff = x; isAvailable(std::pair<int, int>{x + 1, y}) && x - diff != posdiff; ++x);
        }
        break;
    case DOWNPAC:
        for (diff = y; isAvailable(std::pair<int, int>{x, y + 1}) && y - diff != posdiff; ++y);
        if (diff - y != posdiff) {
            for (diff = x; isAvailable(std::pair<int, int>{x - 1, y}) && diff - x != posdiff; --x);
            if (diff == x)
                for (diff = x; isAvailable(std::pair<int, int>{x + 1, y}) && x - diff != posdiff; ++x);
        }
        break;
    default:
        break;
    }
    _manipulate = std::pair<int, int>(x, y);
    return _manipulate;
}

int AI::runAway(queue_node * pos)
{
    int ret = 0;

    int res = rand() % 4;
    if (res == 0) ret = moveUp();
    if (res == 1) ret = moveDown();
    if (res == 2) ret = moveLeft();
    if (res == 3) ret = moveRight();
    return ret;
}

bool AI::closeEnough(std::pair<int, int> & player) {
    int minX = 4;
    int maxX = 4;
    int minY = 4;
    int maxY = 4;

    for (; this->_pos.first - minX < 0; --minX);
    for (; this->_pos.second - minY < 0; --minY );
    for (; this->_pos.first + maxX > (int)this->_map.size(); --maxX);
    for (; this->_pos.second + maxY > (int)this->_map[0].size(); --maxY );

    if ((player.first <= this->_pos.first + maxX && \
        player.first >= this->_pos.first - minX) && \
        (player.second <= this->_pos.second + maxY && \
        player.second >= this->_pos.second - minY))
        return true;
    return false;
}

int AI::getCirclePlayer(std::pair<int, int> & player)
{
    static bool close = false;
    static auto start = std::chrono::system_clock::now();

    if (closeEnough(player)) {
        close = true;
        start = std::chrono::system_clock::now();
    }
    auto end = std::chrono::system_clock::now();
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (close == true && elapsed_ms <= 4000)
        return runAway(pathfinding(player));
    else if (close == true && elapsed_ms > 4000)
        close = false;
    return whichMove(pathfinding(player));
}

bool AI::update(std::pair<int, int> & playerPos, int direction, const std::pair<int, int> & red, bool supermode)
{
    bool ret = false;
    if (supermode)
        return runAway(pathfinding(playerPos));
    if (_id == BLINKY)
        ret = whichMove(pathfinding(playerPos));
    else if (_id == PINKY)
        ret = whichMove(pathfinding(wherePlayerLooking(playerPos, direction)));
    else if (_id == INKY)
        ret = whichMove(pathfinding(getSegment(playerPos, red, direction)));
    else if (_id == CLYDE)
        ret = getCirclePlayer(playerPos);
    else {
        int res = rand() % 4;
        if (res == 0) ret = moveUp();
        if (res == 1) ret = moveDown();
        if (res == 2) ret = moveLeft();
        if (res == 3) ret = moveRight();
    }
    if (playerPos == _pos)
        return 1;
    return ret;
}