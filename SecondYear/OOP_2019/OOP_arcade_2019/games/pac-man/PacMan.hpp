/*
** EPITECH PROJECT, 2020
** PacMan.hpp
** File description:
** pac man
*/

#pragma once

// Project includes
#include "AGameModule.hpp"
#include "ArcadeContent.hpp"
#include "Exception.hpp"

#include "Player.hpp"
#include "AI.hpp"

// C++ includes
#include <memory>
#include <chrono>
#include <iostream>

#define KEY_VALUE event().getKeyValue()
#define CENTER_X (MAP_WIDTH / 2)
#define CENTER_Y (MAP_HEIGHT / 2)

class PacMan : virtual public AGameModule
{
public:
    PacMan(ArcadeContent & arcadeContent);
    ~PacMan();
public:
    enum PageId
    {
        MENU,
        INGAME,
        NAME
    };
    void update() override;
    void updateMenu();
    void updateInGame();
    void updateName();

private:
    bool restart(const std::string & fileName);
    bool dieAndRestart();

    std::pair<int, int> findInMap(const char c);

    void drawMap();
    void loadMap(const std::string & fileName);

    void drawPlayerAndAis();
    void drawBouffe();

    void drawScore();


    void saveScore();
    void readBestScore();

    void player();
    void ai();

    bool checkWin();

private:
    PageId _pageId = PageId::NAME;

    void changePage(PacMan::PageId pageId);

    // Ingame.
    std::vector<std::vector<char>> _oldMap;
    std::vector<std::vector<char>> _pacManMap;
    std::vector<std::vector<char>> _bouffeMap;

    std::unique_ptr<Pacman::Player> _player;
    std::vector<Pacman::AI> _ais;

    int _score = 0;
    int _bestScore = 0;
    int _level = 1;
    int _nbLife = 3;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startAi;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startDie;

    std::string _playerName;
    std::string _bestPlayerName;

    std::string _scorePath;
    std::string _levelPath;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startPlayer;

    // Menu.

    void drawMenu();
    void interactionsMenu();

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startMenu;

    int _menuCursor = 0;

    // Name Panel.

    void drawNamePanel();
    void interactionsNamePanel();

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startAnimName;

    std::string _namePanelCursorString;
    std::pair<int, int> _cursor;

    std::pair<int, int> _aiSpawns[4];
};

extern "C" IGameModule * getGameModule(ArcadeContent & arcadeContent);