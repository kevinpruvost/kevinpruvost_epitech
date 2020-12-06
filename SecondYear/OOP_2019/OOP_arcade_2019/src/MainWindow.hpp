/*
** EPITECH PROJECT, 2020
** MainWindow.hpp
** File description:
** main window
*/

#pragma once

// Project includes
#include "ArcadeDLLoader.hpp"
#include "ArcadeContent.hpp"
#include "ReadDir.hpp"

// C++ includes
#include <map>
#include <memory>

// C includes
#include <stddef.h>
#include <cstring>

#undef EXIT_FAILURE
#define EXIT_FAILURE 84

#define GAME_ID _arcadeContent.event().getGameId()
#define DISPLAY_ID _arcadeContent.event().getDisplayId()
#define GET_EVENT _arcadeContent.event()

#define C_STR_REPO(str) (char *)((exeRepository + str).c_str())

class MainWindow
{
public:
    MainWindow(const int argc, const char * const * argv);
    ~MainWindow();

    int exec(bool pass = true);

    int changeDisplayLib(const std::string & libName);
    int changeGameLib(const std::string & libName);

    void gameLoop();
    void eventActionsWithMainLoop(ArcadeEvent & event, bool & isOver);

private:
    int loadLibs();
    void usageMsg();
    void shortcutLib(std::string &lib);
    bool framePassed();

private:
    const int ac;
    const char * const * av;
    float _fps;
    std::string exeRepository;
    std::unique_ptr<ArcadeDLLoader<IDisplayModule>> _displayLoader = nullptr;
    std::unique_ptr<ArcadeDLLoader<IGameModule>>    _gameLoader    = nullptr;
    std::unique_ptr<IDisplayModule>           _display       = nullptr;
    std::unique_ptr<IGameModule>              _game          = nullptr;

    std::vector<std::string> gameMap;
    std::vector<std::string> displayMap;

    ArcadeContent _arcadeContent;
};