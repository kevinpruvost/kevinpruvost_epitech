/*
** EPITECH PROJECT, 2020
** Sfml.cpp
** File description:
** sfml
*/

#include "Sfml.hpp"

// C++ includes
#include <iostream>
#include <chrono>

Sfml::Sfml(ArcadeContent & arcadeContent)
    : ADisplayModule(arcadeContent, "SFML")
    , _window(sf::VideoMode(WINDOW_X, WINDOW_Y),
              "Arcade Machine - SFML Display Mode",
              sf::Style::Titlebar | sf::Style::Close)
{
    _oldMap.clear();
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        _oldMap.push_back(std::vector<char>());
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            _oldMap[i].push_back(0);
            _objects[i][j] = nullptr;
        }
    }
}

Sfml::~Sfml()
{
    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            if (_objects[i][j])
                delete _objects[i][j];
        }
    }
    _window.close();
}

void Sfml::updateEvent()
{
    static auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();

    if (_window.pollEvent(_event))
        if (_event.type == sf::Event::Closed)
        {
            _window.close();
            setKey(ArcadeEvent::KeyValue::EXIT);
            return;
        }

    if (_event.type == sf::Event::KeyPressed && elapsed_seconds >= 200)
    {
        if (IS_KEY_PRESSED(sf::Keyboard::Left) || IS_KEY_PRESSED(sf::Keyboard::Q))
            setKey(ArcadeEvent::KeyValue::LEFT);
        else if (IS_KEY_PRESSED(sf::Keyboard::Right) || IS_KEY_PRESSED(sf::Keyboard::D))
            setKey(ArcadeEvent::KeyValue::RIGHT);
        else if (IS_KEY_PRESSED(sf::Keyboard::Up) || IS_KEY_PRESSED(sf::Keyboard::Z))
            setKey(ArcadeEvent::KeyValue::UP);
        else if (IS_KEY_PRESSED(sf::Keyboard::Down) || IS_KEY_PRESSED(sf::Keyboard::S))
            setKey(ArcadeEvent::KeyValue::DOWN);
        else if (IS_KEY_PRESSED(sf::Keyboard::Escape))
            setKey(ArcadeEvent::KeyValue::ESCAPE);
        else if (IS_KEY_PRESSED(sf::Keyboard::Return) || IS_KEY_PRESSED(sf::Keyboard::Space))
            setKey(ArcadeEvent::KeyValue::ENTER);
        else if (IS_KEY_PRESSED(sf::Keyboard::X))
            setKey(ArcadeEvent::KeyValue::EXIT);
        else if (IS_KEY_PRESSED(sf::Keyboard::M))
            setKey(ArcadeEvent::KeyValue::MAINMENU);
        else if (IS_KEY_PRESSED(sf::Keyboard::Num1))
            changePrevGraphical();
        else if (IS_KEY_PRESSED(sf::Keyboard::Num2))
            changeNextGraphical();
        else if (IS_KEY_PRESSED(sf::Keyboard::Num3))
            changePrevGame();
        else if (IS_KEY_PRESSED(sf::Keyboard::Num4))
            changeNextGame();
        start = std::chrono::system_clock::now();
    }
}

void Sfml::display()
{
    _window.clear(sf::Color::Black);

    unsigned int wid = 0;
    unsigned int hei = 0;

    for (int i = 0; i < MAP_WIDTH; ++i, wid += SPRITE_WIDTH)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j, hei += SPRITE_HEIGHT)
        {
            if (arcadeMap()[i][j] != _oldMap[i][j])
            {
                if (arcadeMap()[i][j] == 0)
                {
                    if (_objects[i][j])
                    {
                        delete _objects[i][j];
                        _objects[i][j] = nullptr;
                    }
                }
                else
                {
                    try {
                        if (_objects[i][j])
                            delete _objects[i][j];
                        if (_spriteMap.find(arcadeMap()[i][j]) != _spriteMap.end())
                            _objects[i][j] = new sf::Sprite(_spriteMap[arcadeMap()[i][j]]);
                        else
                            _objects[i][j] = nullptr;
                    } catch (std::exception & error) {
                        throw EXCEPTION("Texture '" + arcadeMap()[i][j] + "' doesn't exist.");
                        return;
                    }
                    if (_objects[i][j])
                        _objects[i][j]->setPosition(wid, hei);
                }
            }
            _oldMap[i][j] = arcadeMap()[i][j];
        }
        hei = 0;
    }

    for (int i = 0; i < MAP_WIDTH; ++i)
    {
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            if (_objects[i][j] != nullptr)
                _window.draw(*_objects[i][j]);
        }
    }

    _window.display();
}

void Sfml::setExtraTexture()
{
    _spriteMap.clear();
    _textureMap.clear();
    
    for (int i = 0; i < MAP_WIDTH; ++i)
        for (int j = 0; j < MAP_HEIGHT; ++j)
        {
            _objects[i][j] = nullptr;
            _oldMap[i][j] = 0;
        }

    for (const auto & pair : _spriteInfos)
    {
        const auto & spriteData = pair.second;

        _textureMap.insert(std::make_pair(spriteData.character, sf::Texture()));
        sf::Texture & texture = _textureMap[spriteData.character];
        if (!texture.loadFromFile(spriteData.spritePictureFilename))
        {
            throw EXCEPTION("SFML Exception : Texture '" + spriteData.spritePictureFilename
                + "' cannot be loaded.");
            return;
        }

        _spriteMap.insert(std::make_pair(spriteData.character, sf::Sprite(texture)));
        _spriteMap[spriteData.character].setTextureRect(sf::IntRect(spriteData.spriteLeft,
            spriteData.spriteTop, spriteData.spriteWidth, spriteData.spriteHeight));
        _spriteMap[spriteData.character].setScale(SPRITE_WIDTH  / spriteData.spriteWidth,
                                                  SPRITE_HEIGHT / spriteData.spriteHeight);
    }
}