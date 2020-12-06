/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

// Project includes
#include "Page.hpp"
#include "Pizzas/PizzaFactory.hpp"
#include "Kitchen/Kitchen.hpp"

// C includes
#include <cmath>

#define MAX(x,y) (x)>(y)?(x):(y) 

#define NB_PIZZA_BTNS 4
#define NB_RECTANGLES 3
#define NB_VIEWS 2
#define NB_TEXTS 1

class Game : virtual public Page
{
public:
    enum VIEWS {
        DEFAULT,
        KITCHENS
    };
    enum PIZZAS_BTNS {
        REGINA,
        MARGARITA,
        AMERICANA,
        FANTASIA
    };
    enum RECTANGLES {
        PIZZA_BACKGROUND,
        KITCHEN_BACKGROUND,
        PIZZA,
    };
    enum TEXTS {
        INFO_INPUTS
    };

public:
    Game(sf::RenderWindow & window, sf::Event & event, SfmlIpc & ipc);
    ~Game();

    bool isInBounds(sf::Vector2i pos, sf::RectangleShape rectangle);
    size_t getTextureIdx(Pizza::PizzaType type);
    Pizza::PizzaType getPizzaBtnType(size_t btnIdx);
    
    int exec() override;
    void event(int &, bool &) override;

private:
    sf::Vector2i _lastMousePos;
    sf::Vector2f _lastCenter;

    std::vector<sf::Texture> _pizza_textures;

    sf::Vector2f _windowSize;
    std::vector<sf::View> _views;
    std::vector<std::pair<sf::RectangleShape, sf::Texture>> _rectangles;
    std::vector<std::pair<sf::RectangleShape, sf::Texture>> _pizzaBtns;

    std::vector<sf::Text> _texts;
    sf::Font _laFont;
};

#endif /* !GAME_HPP_ */
