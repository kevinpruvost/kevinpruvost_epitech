/*
** EPITECH PROJECT, 2020
** MainMenu.hpp
** File description:
** MainMenu
*/

#pragma once

// Project includes
#include "ArcadeContent.hpp"
#include "AGameModule.hpp"
#include "Exception.hpp"
#include "ReadDir.hpp"

#define CENTER_X (MAP_WIDTH / 2)
#define QUART_X (MAP_WIDTH / 4)
#define TQUART_X (MAP_WIDTH / 4 * 3)

#define C_STR_REPO(str) (char *)((_exeRepository + str).c_str())

class MainMenu : virtual public AGameModule
{
public:
    MainMenu(ArcadeContent & arcadeContent);
    ~MainMenu();

    void update() override;

    void displayMenu();
    void displayGameLibs();
    void displayGraphLibs();
    void displayLaunch();

    bool animate();

    bool interactions();

    void shortcutLib(std::string & lib);

private:
    std::string _exeRepository;

    std::vector<std::string> gameMap;
    std::vector<std::string> displayMap;

    enum Cursor
    {
        DISPLAY,
        GAME,
        LAUNCH
    };
    int _cursor = Cursor::DISPLAY;
};

extern "C"
{
    IGameModule * getGameModule(ArcadeContent & arcadeContent)
    {
        return new MainMenu(arcadeContent);
    }
}