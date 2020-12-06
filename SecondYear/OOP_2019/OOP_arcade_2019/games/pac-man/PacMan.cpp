/*
** EPITECH PROJECT, 2020
** PacMan.cpp
** File description:
** pacman
*/

#include "PacMan.hpp"

// C++ includes
#include <fstream>
#include <iostream>

using namespace Pacman;

PacMan::PacMan(ArcadeContent & arcadeContent)
    : AGameModule(arcadeContent, "resources/resourcesPacMan")
    , _player { nullptr }
    , _scorePath { "games/pac-man/scores" }
    , _levelPath { "games/pac-man/map/level1" }
    , _namePanelCursorString { "a" }
    , _cursor {0, 0}
{
    _oldMap.resize(MAP_WIDTH);
    _bouffeMap.resize(MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        _oldMap[i].resize(MAP_HEIGHT);
        _bouffeMap[i].resize(MAP_HEIGHT);
    }

    readBestScore();
    restart(_levelPath);
}

PacMan::~PacMan()
{
    saveScore();
}

void PacMan::loadMap(const std::string & fileName)
{
    clearMap();

    std::ifstream f1(fileName);
    std::string s;

    if (!f1.is_open())
    {
        throw EXCEPTION("Map file " + fileName + " cannot be opened.");
        return;
    }

    std::vector<std::string> lines;

    while (std::getline(f1, s, '\n'))
        lines.push_back(s);
    f1.close();

    if (lines.empty() || lines.size() > 30)
    {
        throw EXCEPTION("Map file " + fileName + " is not well formated.");
        return;
    }

    int y = 0;

    _pacManMap.clear();
    _pacManMap.resize(lines[0].length());
    for (int i = 0; i < (int)lines[0].length(); ++i)
        _pacManMap[i].resize(lines.size());

    for (const auto & line : lines)
    {
        if (line.length() > 30 || line.length() != lines[0].length())
        {
            throw EXCEPTION("Map file " + fileName + " is not well formated.");
            return;
        }
        int x = 0;
        for (const auto & c : line)
        {
            _oldMap[x][y] = c;
            _pacManMap[x][y] = c;
            if (c == 'O' || c == '+')
                _bouffeMap[x][y] = c;
            if (c == 'A')
                _aiSpawns[AI::AiIdentities::BLINKY] = std::make_pair(x, y);
            if (c == 'B')
                _aiSpawns[AI::AiIdentities::PINKY] = std::make_pair(x, y);
            if (c == 'C')
                _aiSpawns[AI::AiIdentities::INKY] = std::make_pair(x, y);
            if (c == 'D')
                _aiSpawns[AI::AiIdentities::CLYDE] = std::make_pair(x, y);
            ++x;
        }
        ++y;
    }
}

std::pair<int, int> PacMan::findInMap(const char c)
{
    std::pair<int, int> pos;

    for (int i = 0; i < (int)_pacManMap.size(); ++i)
    {
        for (int j = 0; j < (int)_pacManMap[i].size(); ++j)
        {
            if (_pacManMap[i][j] == c)
            {
                pos.first = i;
                pos.second = j;
                return pos;
            }
        }
    }
    pos.first = -1;
    pos.second = -1;
    return pos;
}

bool PacMan::restart(const std::string & fileName)
{
    loadMap(fileName);

    auto playerPos = findInMap('P');
    auto blinkyPos = findInMap('A');
    auto pinkyPos = findInMap('B');
    auto inkyPos = findInMap('C');
    auto clydePos = findInMap('D');

    try {
        _player.reset(new Player(playerPos, _pacManMap));

        _ais.clear();
        _ais.push_back(AI(AI::AiIdentities::BLINKY, blinkyPos, _pacManMap));
        _ais.push_back(AI(AI::AiIdentities::PINKY,  pinkyPos, _pacManMap));
        _ais.push_back(AI(AI::AiIdentities::INKY,   inkyPos, _pacManMap));
        _ais.push_back(AI(AI::AiIdentities::CLYDE,  clydePos, _pacManMap));
    } catch (std::exception & e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    map()[playerPos.first][playerPos.second] = ' ';
    map()[blinkyPos.first][blinkyPos.second] = ' ';
    map()[pinkyPos.first][pinkyPos.second] = ' ';
    map()[inkyPos.first][inkyPos.second] = ' ';
    map()[clydePos.first][clydePos.second] = ' ';
    drawMap();
    _startAi = std::chrono::system_clock::now();
    _startPlayer = std::chrono::system_clock::now();

    return true;
}

void PacMan::drawMap()
{
    for (int i = 0; i < (int)_pacManMap.size(); ++i)
        for (int j = 0; j < (int)_pacManMap[i].size(); ++j)
        {
            if (_pacManMap[i][j] == '#' || _pacManMap[i][j] == ' '
             || _pacManMap[i][j] == 'O' || _pacManMap[i][j] == '+')
                map()[i][j] = _pacManMap[i][j];
        }
}

void PacMan::player()
{
    _player->update();

    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - _startPlayer).count();;

    if (KEY_VALUE == ArcadeEvent::KeyValue::LEFT)
        _player->setLeft();
    else if (KEY_VALUE == ArcadeEvent::KeyValue::RIGHT)
        _player->setRight();
    else if (KEY_VALUE == ArcadeEvent::KeyValue::UP)
        _player->setUp();
    else if (KEY_VALUE == ArcadeEvent::KeyValue::DOWN)
        _player->setDown();

    if (ms <= 300 - 10 * _level)
        return;

    _startPlayer = std::chrono::system_clock::now();

    int ret = _player->moveForward();

    if (ret >= 0)
    {
        _score += ret;
        for (auto & ai : _ais) {
            if (ai.getPos() == _player->getPos() && _player->getSuper())
                ai.die();
            else if (ai.getPos() == _player->getPos())
                _player->dead() = true;
        }
        if (_bouffeMap[_player->getPos().first][_player->getPos().second] != ' ')
            _bouffeMap[_player->getPos().first][_player->getPos().second] = 0;
    }
    else
    {
        _player->dead() = true;
        return;
    }
}

void PacMan::ai()
{
    auto end = std::chrono::system_clock::now();
    int sec = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end - _startAi).count();

    if (sec >= 400 - 10 * _level)
    {
        _startAi = std::chrono::system_clock::now();
        for (auto & ai : _ais)
        {
            if ((!_player->getSuper()) && ai.isDead())
                ai.setDead(false);
            auto resUpdate = ai.update(_player->getPos(), _player->getDirection(), _ais[0].getPos(), _player->getSuper());
            if (resUpdate == 1 && !_player->getSuper() && ai.getChar() != 'E'
             && ai.getChar() != 'F')
                _player->dead() = true;
            if (resUpdate == 1 && _player->getSuper() && !ai.isDead())
            {
                ai.die();
                _score += 100;
            }
        }
    }
}

void PacMan::readBestScore()
{
    std::ifstream scoreFile(_scorePath);

    if (scoreFile.is_open())
    {
        std::string buffer;
        std::getline(scoreFile, buffer);
        _bestPlayerName = buffer.substr(0, buffer.find(' '));
        buffer = buffer.substr(buffer.find(' ') + 1);
        try {
            _bestScore = std::stoi(buffer);
        } catch (std::exception &) {
            _bestPlayerName.clear();
        }
    }
}

void PacMan::drawScore()
{
    writeCenteredStringOnMap(39, 2, "player");
    writeCenteredStringOnMap(39, 4, _playerName);

    writeCenteredStringOnMap(39, 8, "life");
    writeCenteredStringOnMap(39, 10, std::to_string(_nbLife));

    writeCenteredStringOnMap(39, 14, "level");
    writeCenteredStringOnMap(39, 16, std::to_string(_level));

    writeCenteredStringOnMap(39, 20, "score");
    writeCenteredStringOnMap(39, 22, std::to_string(_score));

    if (_bestScore != 0)
    {
        writeCenteredStringOnMap(39, 26, "highest score");
        writeCenteredStringOnMap(39, 28, "by " + _bestPlayerName);
        writeCenteredStringOnMap(39, 29, std::to_string(_bestScore));
    }
}

void PacMan::saveScore()
{
    if (_score > _bestScore) {
        std::ofstream outFile(_scorePath);
        _bestScore = _score;
        _bestPlayerName = _playerName;
        outFile << _playerName << " " << _score << std::flush;
    }
}

void PacMan::drawPlayerAndAis()
{
    for (const auto & ai : _ais)
    {
        if (_player->getSuper() && ai.getChar() != 'E')
            map()[ai.getPos().first][ai.getPos().second] = 'F';
        else
            map()[ai.getPos().first][ai.getPos().second] = ai.getChar();
    }

    if (!_player->dead())
        map()[_player->getPos().first][_player->getPos().second] = 'P';
}

void PacMan::drawBouffe()
{
    for (unsigned int i = 0; i < _bouffeMap.size(); ++i)
    {
        for (unsigned int j = 0; j < _bouffeMap[0].size(); ++j)
        {
            if (_bouffeMap[i][j] == 'O' || _bouffeMap[i][j] == '+')
                map()[i][j] = _bouffeMap[i][j];
        }
    }
}

bool PacMan::checkWin()
{
    for (const auto & line : _bouffeMap)
    {
        for (const auto c : line)
        {
            if (c == 'O' || c == '+')
                return false;
        }
    }
    return true;
}

bool PacMan::dieAndRestart()
{
    auto end = std::chrono::system_clock::now();
    int sec = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end - _startDie).count();
    if (sec >= 1000)
    {
        this->_nbLife -= 1;
        restart(_levelPath);
        saveScore();
        _level = 1;
        _score = 0;
        return true;
    }
    return false;
}

void PacMan::update()
{
    static const std::vector<void (PacMan::*)()> funcs =
        {&PacMan::updateMenu, &PacMan::updateInGame, &PacMan::updateName};

    (this->*funcs[_pageId])();
}

void PacMan::changePage(PacMan::PageId pageId)
{
    _pageId = pageId;
    if (_pageId == MENU)
        _startMenu = std::chrono::system_clock::now();
}

void PacMan::updateInGame()
{
    if (this->_nbLife == 0)
        setKey(ArcadeEvent::KeyValue::MAINMENU);
    if (_player->dead())
    {
        if (!dieAndRestart())
            return;
    }
    if (checkWin())
    {
        restart(_levelPath);
        ++_level;
    }
    clearMap();
    drawMap();
    player();
    if (_player->dead())
        _startDie = std::chrono::system_clock::now();
    else
        ai();

    drawBouffe();
    drawPlayerAndAis();
    drawScore();

    for (int i = 0; i < (int)_pacManMap.size(); ++i)
        for (int j = 0; j < (int)_pacManMap[0].size(); ++j)
            _pacManMap[i][j] = map()[i][j];

    if (KEY_VALUE == ArcadeEvent::KeyValue::ESCAPE)
        changePage(PacMan::PageId::MENU);
}

extern "C"
{
    IGameModule * getGameModule(ArcadeContent & arcadeContent)
    {
        return new PacMan(arcadeContent);
    }
}