/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Caca
*/

#pragma once

// C++ includes
#include "caca++.h"
#include "caca.h"
#include <iostream>
#include <fstream>

// Project includes
#include "ArcadeContent.hpp"
#include "ADisplayModule.hpp"
#include "SpriteData.hpp"

class ArcadeCaca : virtual public ADisplayModule {
    public:
        ArcadeCaca(ArcadeContent & ArcadeContent);
        ~ArcadeCaca();

        void updateEvent() override;
        void setExtraTexture() override;
        void display() override;

    private:
        caca_canvas_t *_cv;
        caca_display_t *_dp;
        caca_event_t _ev;
};

extern "C"
{
    IDisplayModule * getDisplayModule(ArcadeContent & arcadeContent)
    {
        return new ArcadeCaca(arcadeContent);
    }
}