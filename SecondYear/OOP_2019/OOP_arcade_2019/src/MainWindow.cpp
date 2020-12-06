/*
** EPITECH PROJECT, 2020
** MainWindow.cpp
** File description:
** main window
*/

#include "MainWindow.hpp"

// C++ includes
#include <algorithm>
#include <iostream>
#include <csignal>
#include <cstring>
#include <chrono>

#define GameId ArcadeEvent::GameId
#define DisplayId ArcadeEvent::DisplayId

bool isOver = false;

MainWindow::MainWindow(const int argc, const char * const * argv)
    : ac { argc }
    , av { argv }
    , _fps { 30 }
    , exeRepository { av[0] }
{
    std::replace(exeRepository.begin(), exeRepository.end(), '\\', '/');
    exeRepository = exeRepository.substr(0, exeRepository.find_last_of('/'));
    exeRepository += '/';
}

MainWindow::~MainWindow()
{
}

void MainWindow::usageMsg()
{
    if (displayMap.empty())
    {
        std::cerr << "But there's no graphical libraries detected in lib/\n" << std::endl;
        std::cerr << "          ¯\\_(ツ)_/¯\n" << std::endl;
        return;
    }

    std::cerr << "You must use one of these graphical libraries :" << std::endl;
    for (const auto & display : displayMap)
        std::cerr << "./arcade " << display << std::endl;
    std::cerr << std::endl;
    std::cerr << "Or one of these shortcuts :" << std::endl;
    for (const auto & display : displayMap)
    {
        std::cerr << "./arcade "
        << display.substr(strlen("./lib/lib_arcade_"),
        display.size() - strlen(".so") - strlen("./lib/lib_arcade_")) << std::endl;
    }
    std::cerr << std::endl;
}

void MainWindow::shortcutLib(std::string & lib)
{
    for (const auto & display : displayMap)
    {
        if (lib == display.substr(strlen(C_STR_REPO("lib/lib_arcade_")),
                   display.size() - strlen(".so") - strlen(C_STR_REPO("lib/lib_arcade_"))))
        {
            lib = display;
            return;
        }
    }
}

int MainWindow::loadLibs()
{
    try {
        const auto libDirFileNames = ReadDir::getDirectoryFilenames(C_STR_REPO("lib"));
        const auto gameDirFileNames = ReadDir::getDirectoryFilenames(C_STR_REPO("games"));

        for (const auto & name : libDirFileNames)
        {
            if (name.size() >= strlen("lib_arcade_.so")
             && name.substr(0, strlen("lib_arcade_")).compare("lib_arcade_") == 0
             && name.substr(name.size() - strlen(".so"), name.size()).compare(".so") == 0)
                displayMap.push_back(exeRepository + "lib/" + std::string(name));
        }

        for (const auto & name : gameDirFileNames)
        {
            if (name.size() >= strlen("lib_arcade_.so")
             && name.substr(0, strlen("lib_arcade_")).compare("lib_arcade_") == 0
             && name.substr(name.size() - strlen(".so"), name.size()).compare(".so") == 0)
                gameMap.push_back(exeRepository + "games/" + std::string(name));
        }
    } catch (const std::exception & e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int MainWindow::changeDisplayLib(const std::string & libName)
{
    _display.reset();


    _displayLoader.reset();

    try {
        _displayLoader = std::make_unique<ArcadeDLLoader<IDisplayModule>>(libName);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (_displayLoader->isError())
        return EXIT_FAILURE;

    try {
        _display.reset(_displayLoader->getInstance("getDisplayModule", _arcadeContent));
        if (!_display)
            throw EXCEPTION("No display instance loaded.");
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    if (!_display)
        return EXIT_FAILURE;

    try {
        _display->setTexture(exeRepository + _game->getTextureFilepath());
    } catch (const std::exception & error) {
        std::cerr << error.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int MainWindow::changeGameLib(const std::string & libName)
{
    _game.reset();

    _gameLoader.reset();
    try {
        _gameLoader = std::make_unique<ArcadeDLLoader<IGameModule>>(libName);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    

    if (_gameLoader->isError())
        return EXIT_FAILURE;

    try {
        _game.reset(_gameLoader->getInstance("getGameModule", _arcadeContent));
        if (!_game)
            throw EXCEPTION("No game instance loaded.");
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }


    if (!_game)
        return EXIT_FAILURE;
    if (_display)
    {
        try {
            _display->setTexture(exeRepository + _game->getTextureFilepath());
        } catch (const std::exception & error) {
            std::cerr << error.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int MainWindow::exec(bool pass)
{
    if (loadLibs() == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (ac != 2 || std::string(av[1]) == "-h" || std::string(av[1]) == "--help")
    {
        std::cerr << "\nUsage : ./arcade GRAPHIC_LIBRARY" << std::endl;
        usageMsg();
        return EXIT_FAILURE;
    }

    std::string lib = av[1];
    shortcutLib(lib);

    if (gameMap.empty())
    {
        std::cerr << "There's no games to load in games/." << std::endl;
        return EXIT_FAILURE;
    }

    if (displayMap.empty())
    {
        std::cerr << "There's no graphical libraries to load in lib/." << std::endl;
        return EXIT_FAILURE;
    }

    if (changeGameLib(C_STR_REPO(Constants::libPaths::mainmenu)) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (changeDisplayLib(lib) == EXIT_FAILURE)
        return EXIT_FAILURE;

    for (unsigned int i = 0; i < displayMap.size(); ++i)
        if (displayMap[i] == lib)
            DISPLAY_ID = i;

    if (pass)
        gameLoop();

    return EXIT_SUCCESS;
}

void signalHandler(int signum)
{
    if (signum == SIGINT)
        isOver = true;
}

void MainWindow::eventActionsWithMainLoop(ArcadeEvent & event, bool & isOver)
{
    const auto keyValue = event.getKeyValue();

    if (keyValue == ArcadeEvent::KeyValue::NO_KVALUE)
        return;

    if (keyValue == ArcadeEvent::KeyValue::EXIT)
    {
        isOver = true;
        return;
    }

    if (keyValue == ArcadeEvent::KeyValue::CHANGE_GAME)
    {
        if (GAME_ID >= (int)gameMap.size())
            GAME_ID = 0;
        if (GAME_ID < 0)
            GAME_ID = gameMap.size() - 1;
        if (changeGameLib(gameMap[GAME_ID]) == EXIT_FAILURE)
        {
            isOver = true;
            return;
        }
    }
    else if (keyValue == ArcadeEvent::KeyValue::CHANGE_GRAPH)
    {
        if (DISPLAY_ID >= (int)displayMap.size())
            DISPLAY_ID = 0;
        if (DISPLAY_ID < 0)
            DISPLAY_ID = displayMap.size() - 1;
        if (changeDisplayLib(displayMap[DISPLAY_ID]) == EXIT_FAILURE)
        {
            isOver = true;
            return;
        }
    }
    else if (keyValue == ArcadeEvent::KeyValue::MAINMENU)
    {
        if (changeGameLib(C_STR_REPO(Constants::libPaths::mainmenu)) == EXIT_FAILURE)
        {
            std::cerr << "Error while loading main menu." << std::endl;
            isOver = true;
            return;
        }
        GAME_ID = -1;
    }
}

bool MainWindow::framePassed()
{
    // les sleep sont mieux, plus opti
    static auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (elapsed_ms >= (1.0000f / _fps) * 1000)
    {
        start = std::chrono::system_clock::now();
        return true;
    }
    return false;
}

#include <unistd.h>

void MainWindow::gameLoop()
{
    signal(SIGINT, signalHandler);

    while (!isOver)
    {
        //if (!framePassed())
        //    continue;
        usleep(1.000f / _fps * 1000000);
        try {
            _display->updateEvent();
            eventActionsWithMainLoop(GET_EVENT, isOver);
            if (isOver)
                continue;
            _game->update();
            _display->display();
        } catch (std::exception & e) {
            std::cout << e.what() << std::endl;
            isOver = true;
        }
        eventActionsWithMainLoop(GET_EVENT, isOver);
        _arcadeContent.event().getKeyValue() = ArcadeEvent::KeyValue::NO_KVALUE;
    }
}