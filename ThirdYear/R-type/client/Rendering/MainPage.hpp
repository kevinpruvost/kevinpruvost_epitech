/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MainPage
*/

#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace RType
{
namespace Client 
{
namespace Rendering 
{
    class MainPage {
        public:
            MainPage();
            ~MainPage();

            void Start();

        private:
            sf::RenderWindow _window;
            std::vector<sf::Texture> _texture;
            sf::Sprite _sprite;
            sf::Font _font;
            //sf::Music _music;
            sf::Event _event;
    };
};
};
};