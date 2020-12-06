/*
** EPITECH PROJECT, 2020
** Menu.cpp
** File description:
** pacman menu
*/

#include "PacMan.hpp"

void PacMan::interactionsMenu()
{
    if (KEY_VALUE == ArcadeEvent::KeyValue::UP)
    {
        --_menuCursor;
        if (_menuCursor < 0)
            _menuCursor = 2;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::DOWN)
    {
        ++_menuCursor;
        if (_menuCursor > 2)
            _menuCursor = 0;
    }
    else if (KEY_VALUE == ArcadeEvent::KeyValue::ENTER)
    {
        if (_menuCursor == 0)
            changePage(PacMan::PageId::INGAME);
        else if (_menuCursor == 1)
            setKey(ArcadeEvent::KeyValue::MAINMENU);
        else
            setKey(ArcadeEvent::KeyValue::EXIT);
    }
}

void PacMan::drawMenu()
{
    static auto start = std::chrono::system_clock::now();
    static bool animate = false;
    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (ms >= 400)
    {
        start = std::chrono::system_clock::now();
        animate = !animate;
    }

    if (_menuCursor == 0 && !animate)
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 1, "> resume <");
    else
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 1, "resume");

    if (_menuCursor == 1 && !animate)
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 2, "> main menu <");
    else
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 2, "main menu");

    if (_menuCursor == 2 && !animate)
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 3, "> quit <");
    else
        writeCenteredStringOnMap(MAP_WIDTH / 2, MAP_HEIGHT / 5 * 3, "quit");
}

void PacMan::updateMenu()
{
    clearMap();

    interactionsMenu();
    drawMenu();
    auto end = std::chrono::system_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - _startAi).count();
    _startMenu = std::chrono::system_clock::now();
    _startAi += std::chrono::milliseconds(ms);
    _startDie += std::chrono::milliseconds(ms);
    _startPlayer += std::chrono::milliseconds(ms);
    _player->resetTime(std::chrono::milliseconds(ms));
}