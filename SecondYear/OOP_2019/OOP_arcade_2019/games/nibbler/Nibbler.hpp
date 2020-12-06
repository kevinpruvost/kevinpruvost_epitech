/*
** EPITECH PROJECT, 2020
** Nibbler.hpp
** File description:
** nibbler
*/

#pragma once

// Project includes
#include "ArcadeContent.hpp"
#include "AGameModule.hpp"
#include <iostream>
#include <fstream>
#include <chrono>

#define RIGHTSNAKE   2
#define LEFTSNAKE    1
#define UPSNAKE      0
#define DOWNSNAKE    3

class Nibbler : virtual public AGameModule
{
public:
    Nibbler(ArcadeContent & arcadeContent);
    ~Nibbler();

    std::string parsLine(const std::string &);
    void loadBestScore();
    void setScore();
    void setName();
    bool animate();

    void loadNextLevel(bool);
    void chargeCunsomable();
    void deleteCunsomable(unsigned int, unsigned int);
    void displayInformationGame();
    void displayMap();
    void foundSnake();
    void writeLineOnMap(int, int, std::string);
    void nibblerMapClear();
    int centerHorizontalMap(int);
    int centerVertcalMap(int);
    void EscapeMenu();

    void update() override;
    void moveSnake();
    void grow(int, int);
    void moveSnakeUp();
    void moveSnakeDown();
    void moveSnakeRight();
    void moveSnakeLeft();
    bool checkDead();
    void moveBody(int, int);
    int orientation();
    bool doMove();
    void automoveLeft();
    void automoveRight();
    void automoveUp();
    void automoveDown();

private:
    std::string __defaultPath = "games/nibbler/map/";
    std::vector<std::string> __pathArray = {__defaultPath + "map1.txt", __defaultPath + "map2.txt"};
    std::vector<std::pair<unsigned int, unsigned int>> __snakePosition;
    std::vector<std::vector<char>> __nibblerMap;
    std::vector<std::vector<char>> __saveNibblerMap;
    std::string __pathScore = "games/nibbler/bestScore";
    std::string __namePlayer1 = "default";
    std::string __nameBestScore;
    unsigned int __level = 0;
    unsigned int __max_level = 2;
    unsigned int __bestScore = 0;
    unsigned int __snakeLength = 4;
    unsigned int __score = 0;
    unsigned int __headX = 0;
    unsigned int __headY = 0;
    unsigned int __tailX = 0;
    unsigned int __tailY = 0;
    int __nbrLife = 3;
    int __yMenu = 0;
    int __xMenu = 0;
    int __time = 500;
    int __yEscapeMenu = 0;
    int __nbConsomable = 0;
    bool __EscapeMenuEnable = false;
};

extern "C"
{
    IGameModule * getGameModule(ArcadeContent & arcadeContent)
    {
        return new Nibbler(arcadeContent);
    }
}
