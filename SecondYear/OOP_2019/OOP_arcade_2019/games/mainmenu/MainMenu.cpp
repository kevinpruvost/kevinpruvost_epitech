/*
** EPITECH PROJECT, 2020
** MainMenu.cpp
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

// C++ includes
#include <cstring>
#include <iostream>
#include <chrono>

// C includes
#include <dirent.h>

MainMenu::MainMenu(ArcadeContent & arcadeContent)
try : AGameModule(arcadeContent, "resources/resourcesMainMenu")
{
    const auto libDirFileNames = ReadDir::getDirectoryFilenames(C_STR_REPO("lib"));
    const auto gameDirFileNames = ReadDir::getDirectoryFilenames(C_STR_REPO("games"));
    
    for (const auto & name : libDirFileNames)
    {
        if (name.size() >= strlen("lib_arcade_.so")
         && name.substr(0, strlen("lib_arcade_")).compare("lib_arcade_") == 0
         && name.substr(name.size() - strlen(".so"), name.size()).compare(".so") == 0)
            displayMap.push_back(_exeRepository + "lib/" + std::string(name));
    }
    
    for (const auto & name : gameDirFileNames)
    {
        if (name.size() >= strlen("lib_arcade_.so")
         && name.substr(0, strlen("lib_arcade_")).compare("lib_arcade_") == 0
         && name.substr(name.size() - strlen(".so"), name.size()).compare(".so") == 0)
            gameMap.push_back(_exeRepository + "games/" + std::string(name));
    }

    for (unsigned int i = 0; i < displayMap.size(); ++i)
        shortcutLib(displayMap[i]);

    for (unsigned int i = 0; i < gameMap.size(); ++i)
        shortcutLib(gameMap[i]);

} catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
}

MainMenu::~MainMenu()
{
}

void MainMenu::shortcutLib(std::string & lib)
{
    if (lib.substr(0, strlen(C_STR_REPO("lib"))) == C_STR_REPO("lib"))
    {
        lib = lib.substr(strlen(C_STR_REPO("lib/lib_arcade_")),
               lib.size() - strlen(".so") - strlen(C_STR_REPO("lib/lib_arcade_")));
        return;
    }
    else if (lib.substr(0, strlen(C_STR_REPO("games"))) == C_STR_REPO("games"))
    {
        lib = lib.substr(strlen(C_STR_REPO("games/lib_arcade_")),
               lib.size() - strlen(".so") - strlen(C_STR_REPO("games/lib_arcade_")));
        return;
    }
    else
    {
        throw EXCEPTION(lib + " name is not well formated");
        return;
    }
}

bool MainMenu::animate()
{
    static bool anim = false;
    static auto start = std::chrono::system_clock::now();

    auto end = std::chrono::system_clock::now();
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (elapsed_ms >= 400)
    {
        start = std::chrono::system_clock::now();
        anim = !anim;
    }
    return anim;
}

void MainMenu::displayGraphLibs()
{
    auto id = _arcadeContent.event().getDisplayId();

    std::string str1;
    std::string str2;
    std::string str3;

    str2 = displayMap[id];    

    str1 = (id <= 0) ? displayMap[displayMap.size() - 1] : displayMap[id - 1];
    str3 = ((size_t)id >= displayMap.size() - 1) ? displayMap[0] : displayMap[id + 1];

    if (_cursor != Cursor::DISPLAY || !animate())
        writeCenteredStringOnMap(CENTER_X, 14, str2);
    else
        writeCenteredStringOnMap(CENTER_X, 14, "> " + str2 + " <");
    writeCenteredStringOnMap(QUART_X - str2.size()  / 2, 14, str1);
    writeCenteredStringOnMap(TQUART_X + str2.size() / 2, 14, str3);
}

void MainMenu::displayGameLibs()
{
    auto id = _arcadeContent.event().getGameId();

    std::string str1;
    std::string str2;
    std::string str3;

    str2 = (id == -1) ? "no game" : gameMap[id];
    str1 = (id <= 0) ? gameMap[gameMap.size() - 1] : gameMap[id - 1];
    str3 = ((size_t)id >= gameMap.size() - 1) ? gameMap[0] : gameMap[id + 1];

    if (_cursor != Cursor::GAME || !animate())
        writeCenteredStringOnMap(CENTER_X, 22, str2);
    else
        writeCenteredStringOnMap(CENTER_X, 22, "> " + str2 + " <");
    writeCenteredStringOnMap(QUART_X - str2.size()  / 2, 22, str1);
    writeCenteredStringOnMap(TQUART_X + str2.size() / 2, 22, str3);
}

void MainMenu::displayLaunch()
{
    std::string str = "launch";

    if (_cursor != Cursor::LAUNCH || !animate())
        writeCenteredStringOnMap(CENTER_X, 26, str);
    else
        writeCenteredStringOnMap(CENTER_X, 26, "> " + str + " <");
}

void MainMenu::displayMenu()
{
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        map()[i][0] = '#';
        map()[i][MAP_HEIGHT - 1] = '#';
    }

    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        map()[0][i] = '#';
        map()[MAP_WIDTH - 1][i] = '#';
    }

    writeCenteredStringOnMap(CENTER_X, 2, "arcade");
    writeCenteredStringOnMap(CENTER_X, 3, "machine");
    writeCenteredStringOnMap(CENTER_X, 5, "main menu");

    writeCenteredStringOnMap(CENTER_X, 10, "display mode");
    writeCenteredStringOnMap(CENTER_X, 18, "game");
}

void MainMenu::update()
{
    clearMap();
    displayMenu();
    displayGraphLibs();
    displayGameLibs();
    displayLaunch();
    interactions();
}

bool MainMenu::interactions()
{
    if (_arcadeContent.event().getKeyValue() == ArcadeEvent::KeyValue::UP)
    {
        --_cursor;
        (_cursor < Cursor::DISPLAY) ? _cursor = Cursor::LAUNCH : 0;
    }
    else if (_arcadeContent.event().getKeyValue() == ArcadeEvent::KeyValue::DOWN)
    {
        ++_cursor;
        (_cursor > Cursor::LAUNCH) ? _cursor = Cursor::DISPLAY : 0;
    }
    else if (_arcadeContent.event().getKeyValue() == ArcadeEvent::KeyValue::LEFT)
    {
        if (_cursor == Cursor::DISPLAY)
        {
            changePrevGraphical();
            return false;
        }
        else if (_cursor == Cursor::GAME)
        {
            if (_arcadeContent.event().getGameId() - 1 < 0)
                _arcadeContent.event().getGameId() = gameMap.size() - 1;
            else
                --_arcadeContent.event().getGameId();
        }
    }
    else if (_arcadeContent.event().getKeyValue() == ArcadeEvent::KeyValue::RIGHT)
    {
        if (_cursor == Cursor::DISPLAY)
        {
            changeNextGraphical();
            return false;
        }
        else if (_cursor == Cursor::GAME)
        {
            if (_arcadeContent.event().getGameId() + 1 >= (int)gameMap.size())
                _arcadeContent.event().getGameId() = 0;
            else
                ++_arcadeContent.event().getGameId();
        }
    }
    else if (_arcadeContent.event().getKeyValue() == ArcadeEvent::KeyValue::ENTER)
    {
        if (_cursor == LAUNCH && _arcadeContent.event().getGameId() != -1)
        {
            setKey(ArcadeEvent::KeyValue::CHANGE_GAME);
            return false;
        }
    }
    return true;
}