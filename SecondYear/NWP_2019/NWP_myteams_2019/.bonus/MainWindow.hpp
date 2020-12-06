/*
** A Kevin Pruvost's project, May 2020
** MainWindow.hpp
** File description:
** main
*/

#pragma once

// Project includes
#include "Client.hpp"

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>

class MainWindow
{
public:
    MainWindow(int ac, char ** av);
    ~MainWindow();

    int exec();

    void chatPanel();

private:
    std::string getChar();
    void drawUsers();
    void drawMsg();

protected:
private:
    sf::RenderWindow _window;
    sf::Event _event;

    int _page;

    KVector<sf::Texture> _textures;
    KVector<sf::Sprite> _sprites;

    sf::Font font;

    sf::Text _usersText;
    sf::Text _msgText;
    sf::Text _inputText;

    Client client;
};