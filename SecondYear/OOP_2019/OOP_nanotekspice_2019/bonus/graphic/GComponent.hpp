/*
** EPITECH PROJECT, 2020
** GComponent.hpp
** File description:
** gcomp
*/

#pragma once

// Project includes
#include "Constants.hpp"

#include "Component.hpp"

// Libs includes
#include <SFML/Graphics.hpp>

class GComponent
{
public:
    GComponent(const nts::IComponent & comp);
    ~GComponent();

    bool operator==(const nts::IComponent & comp1) const;
    sf::Sprite & getSprite();
    void refresh();

public:
    const nts::IComponent & _comp;
    sf::Sprite _sprite;
    sf::Text _name;
};
