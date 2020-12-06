/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

// Project includes
#include "Page.hpp"

#define MOUSE_IN(mousePos, pos, text) \
    (mousePos.x >= pos.x - text.width / 2 && mousePos.x <= pos.x + text.width / 2) \
    && (mousePos.y >= pos.y - text.height / 2 && mousePos.y <= pos.y + text.height / 2)

class Menu : virtual public Page
{
public:
    Menu(sf::RenderWindow & window, sf::Event & event, SfmlIpc & ipc);
    ~Menu();

    enum Icons {
        Background = 0,
        Play,
        Quit,
        Last
    };

    int exec() override;
    void event(int &, bool &) override;
    void animations();
private:
    std::vector<std::pair<sf::Texture, sf::Sprite>> map_texture;
    sf::Text text;
    sf::Font font;
    sf::Music _music;
    sf::VideoMode videoMode;
};

#endif /* !MENU_HPP_ */
