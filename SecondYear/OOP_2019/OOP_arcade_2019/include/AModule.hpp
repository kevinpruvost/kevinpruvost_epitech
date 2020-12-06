/*
** EPITECH PROJECT, 2020
** AModule.hpp
** File description:
** amodule
*/

#pragma once

// Project includes
#include "ArcadeContent.hpp"

class AModule
{
protected:
    AModule(ArcadeContent & arcadeContent);
    ~AModule();

    void setKey(ArcadeEvent::KeyValue key);
    void changePrevGame();
    void changeNextGame();
    void changeNextGraphical();
    void changePrevGraphical();

    ArcadeEvent::KeyValue getKey();

    void clearMap();
    std::vector<std::vector<char>> & map();
    ArcadeEvent & event();

protected:
    ArcadeContent & _arcadeContent;
};