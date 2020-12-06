/*
** EPITECH PROJECT, 2020
** Sdl.hpp
** File description:
** sfml
*/

#pragma once

// C++ includes
#include <map>
#include <vector>
#include <memory>

// SDL includes
#include "SDL.h"
#include "SDL_image.h"

// Project includes
#include "ADisplayModule.hpp"

#define IS_KEY_PRESSED(keyI) event.key.keysym.sym == keyI

class Sdl : virtual public ADisplayModule
{
public:
    Sdl(ArcadeContent & arcadeContent);
    ~Sdl();

    void updateEvent() override;
    void setExtraTexture() override;
    void display() override;

private:
    std::map<char, SDL_Texture *> _textureMap;
    std::map<char, SDL_Rect> _spriteData;

    std::vector<std::vector<char>> _oldMap;

    SDL_Window * _window;
    SDL_Renderer * _renderer;

    int scaleX;
    int scaleY;
};

extern "C"
{
    IDisplayModule * getDisplayModule(ArcadeContent & arcadeContent)
    {
        return new Sdl(arcadeContent);
    }
}