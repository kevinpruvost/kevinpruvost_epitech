/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SpaceInvader
*/

#ifndef SPACEINVADER_HPP_
#define SPACEINVADER_HPP_

// Project includes
#include "AGameModule.hpp"
#include "ArcadeContent.hpp"
#include "Exception.hpp"

#include "Player.hpp"
#include "Ennemy.hpp"
#include "Bridge.hpp"

//C++ includes
#include <memory>
#include <iostream>
#include <chrono>
#include <fstream>

#define KEY_VALUE event().getKeyValue()
#define CENTER_X (MAP_WIDTH / 2)
#define CENTER_Y (MAP_HEIGHT / 2)

class SpaceInvader : virtual public AGameModule
{
public:
    enum PageId
    {
        MENU,
        INGAME,
        NAME,
        SCORE
    };
    SpaceInvader(ArcadeContent &arcadeContent);
    ~SpaceInvader();
    void update() override;
    void updateMenu();
    void updateInGame();
    void updateScorePage();
    void updateName();
    void writeLineOnMap(int, int, std::string);
    bool animate();

    void loadMap(const std::string &fileName);
    std::pair<int, int> findInMap(const char c);
    std::pair<int, int > findExtremAI(int);
    std::vector<std::pair<int, int>> findInMapVector(const char c);
    int FindEnemy(std::pair<int, int>);
    int FindBridge(std::pair<int, int>);
    bool restart(const std::string &fileName);
    void drawMap();
    void readBestScore();
    void drawScore();
    bool checkWin();
    void player();
    void enemy();
    void shootPlayerAndEnemy();
    void shootEnemy();
    void downAI();

protected:
private:
    //Ingame
    std::vector<std::vector<char>> _invaderMap;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startPlayer;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startEnemy;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _shootEnemy;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _shootPlayer;

    int _level;
    int _nbLife;
    // Menu
    PageId _pageId = PageId::NAME;

    void changePage(SpaceInvader::PageId pageId);

    void drawMenu();
    void saveScore();
    void interactionsMenu();

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startMenu;

    int _menuCursor = 0;

    // Name Panel.

    std::string _playerName;
    std::string _bestPlayerName;
    int _score = 0;
    int _bestScore = 0;

    std::unique_ptr<Spaceinvader::Player> _player;
    std::vector<Spaceinvader::Bridge> _bridge;
    std::vector<Spaceinvader::Ennemy> _ennemy;

    std::string _scorePath;
    std::string _levelPath;

    void drawNamePanel();
    void interactionsNamePanel();

    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> _startAnimName;

    std::string _namePanelCursorString;
    std::pair<int, int> _cursor;
};

extern "C" IGameModule *getGameModule(ArcadeContent &arcadeContent);

#endif /* !SPACEINVADER_HPP_ */
