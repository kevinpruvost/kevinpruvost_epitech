/*
** EPITECH PROJECT, 2020
** Ncurses.hpp
** File description:
** ncurses
*/

#pragma once

// C++ includes
#include <map>
#include <fstream>
#include <iostream>
#include <ncurses.h>
#include <math.h>

// Project includes
#include "ArcadeContent.hpp"
#include "ADisplayModule.hpp"
#include "SpriteData.hpp"

// Window x size : 50 Double la width -> 100
// Window y size : 30

#define COLOR   1
#define KEXIT   27

class Ncurses : virtual public ADisplayModule
{
public:
    Ncurses(ArcadeContent & arcadeContent);
    ~Ncurses();

    void updateEvent() override;
    void setExtraTexture() override;
    void display() override;

    void create_newwin(int height, int width, int starty, int startx);

private:
    bool _color = true;

    std::map<char, short int> _colorMap;
};

extern "C"
{
    IDisplayModule * getDisplayModule(ArcadeContent & arcadeContent)
    {
        return new Ncurses(arcadeContent);
    }
}