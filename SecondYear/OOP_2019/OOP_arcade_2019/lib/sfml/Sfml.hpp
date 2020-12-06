/*
** EPITECH PROJECT, 2020
** Sfml.hpp
** File description:
** sfml
*/

#pragma once

// C++ includes
#include <map>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Project includes
#include "ADisplayModule.hpp"

#define IS_KEY_PRESSED(key) sf::Keyboard::isKeyPressed(key)

class Sfml : virtual public ADisplayModule
{
public:
    Sfml(ArcadeContent & arcadeContent);
    ~Sfml();

    void updateEvent() override;
    void setExtraTexture() override;
    void display() override;

private:
    std::map<char, sf::Texture> _textureMap;
    std::map<char, sf::Sprite> _spriteMap;

    std::vector<std::vector<char>> _oldMap;

    sf::Sprite * _objects[MAP_WIDTH][MAP_HEIGHT];

    sf::Event _event;
    sf::RenderWindow _window;

    int scaleX;
    int scaleY;
};

extern "C"
{
    IDisplayModule * getDisplayModule(ArcadeContent & arcadeContent)
    {
        return new Sfml(arcadeContent);
    }
}