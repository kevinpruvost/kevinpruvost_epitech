/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Menu
*/

#include "Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow & window, sf::Event & event, SfmlIpc & ipc)
    : Page(window, event, ipc)
    , videoMode { sf::VideoMode::getDesktopMode() }
{
    _music.openFromFile("./bonus/resources/menu_music.ogg");
    _music.play();
    _music.setLoop(true);

    font.loadFromFile("./bonus/resources/Pacifico.ttf");
    text.setFont(font);
    text.setString("Des Freds et des Fourchettes");
    text.setCharacterSize(60);
    text.setPosition(videoMode.width / 2 - (text.getGlobalBounds().width / 2), videoMode.height * 0.2);
    text.setFillColor({255, 240, 74});
    text.setStyle(sf::Text::Bold);

    for (int i = 0; i < Last; ++i)
        map_texture.push_back(std::pair<sf::Texture, sf::Sprite>{sf::Texture(), sf::Sprite()});

    map_texture[Background].first.loadFromFile("./bonus/resources/background_menu.png");
    map_texture[Play].first.loadFromFile("./bonus/resources/play_button.png");
    map_texture[Quit].first.loadFromFile("./bonus/resources/quit_button.png");
    map_texture[Play].second.setTexture(map_texture[Play].first);
    map_texture[Quit].second.setTexture(map_texture[Quit].first);

    map_texture[Background].second.setTexture(map_texture[Background].first);
    map_texture[Background].second.setScale(videoMode.width / map_texture[Background].second.getGlobalBounds().width
    , videoMode.height / map_texture[Background].second.getGlobalBounds().height);

    map_texture[Play].second.setOrigin(map_texture[Play].second.getGlobalBounds().width / 2,
                                       map_texture[Play].second.getGlobalBounds().height / 2);
    map_texture[Quit].second.setOrigin(map_texture[Quit].second.getGlobalBounds().width / 2,
                                       map_texture[Quit].second.getGlobalBounds().height / 2);

    map_texture[Play].second.setPosition(videoMode.width / 2, videoMode.height * 0.45);
    map_texture[Quit].second.setPosition(videoMode.width / 2, videoMode.height * 0.65);
}

Menu::~Menu()
{
}

int Menu::exec()
{
    animations();
    for (int i = 0; i < Last; ++i)
        _window.draw(map_texture[i].second);
    _window.draw(text);
    return EXIT_SUCCESS;
}

void Menu::animations()
{
    auto pos = sf::Mouse::getPosition(_window);

    const auto & pos_play = map_texture[Play].second.getPosition();
    const auto & size_play = map_texture[Play].second.getGlobalBounds();

    const auto & pos_quit = map_texture[Quit].second.getPosition();
    const auto & size_quit = map_texture[Quit].second.getGlobalBounds();

    if (MOUSE_IN(pos, pos_play, size_play))
        map_texture[Play].second.setScale(1.2, 1.2);
    else
        map_texture[Play].second.setScale(1, 1);

    if (MOUSE_IN(pos, pos_quit, size_quit))
        map_texture[Quit].second.setScale(1.2, 1.2);
    else
        map_texture[Quit].second.setScale(1, 1);
}

void Menu::event(int & page, bool & workingProcess)
{
    if (_event.type != sf::Event::MouseButtonReleased
     || _event.mouseButton.button != sf::Mouse::Left)
        return;

    auto pos = sf::Mouse::getPosition(_window);

    const auto & pos_play = map_texture[Play].second.getPosition();
    const auto & size_play = map_texture[Play].second.getGlobalBounds();

    const auto & pos_quit = map_texture[Quit].second.getPosition();
    const auto & size_quit = map_texture[Quit].second.getGlobalBounds();

    if (MOUSE_IN(pos, pos_play, size_play))
        page = 1;

    if (MOUSE_IN(pos, pos_quit, size_quit))
    {
        _music.stop();
        _window.close();
        workingProcess = false;
    }
}