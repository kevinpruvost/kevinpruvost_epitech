/*
** EPITECH PROJECT, 2020
** GComponent.cpp
** File description:
** gcomp
*/

#include "GComponent.hpp"

sf::Texture inputTexture;
sf::Texture outputTexutre;
sf::Texture componentTexture;
sf::Font font;

GComponent::GComponent(const nts::IComponent & comp)
    : _comp { comp }
    , _name {}
{
    static bool init = false;

    if (!init)
    {
        inputTexture.loadFromFile(Constants::inputPath);
        outputTexutre.loadFromFile(Constants::outputPath);
        componentTexture.loadFromFile(Constants::componentPath);
        font.loadFromFile(Constants::fontPath);
        init = true;
    }

    _name.setString(_comp.getName());
    _name.setFont(font);
    _name.setCharacterSize(10);

    if (_comp.getComponentType() == nts::ComponentType::INPUT)
        _sprite.setTexture(inputTexture);
    else if (_comp.getComponentType() == nts::ComponentType::COMPONENT)
        _sprite.setTexture(componentTexture);
    else
        _sprite.setTexture(outputTexutre);
    refresh();
}

void GComponent::refresh()
{
    static sf::Color green(50, 255, 50, 255);
    static sf::Color red(255, 50, 50, 255);
    static sf::Color undef(255, 255, 255, 50);

    if (_comp.getComponentType() == nts::ComponentType::INPUT
     || _comp.getComponentType() == nts::ComponentType::OUTPUT)
    {
        _sprite.setColor(
            (_comp.getValue(1) == nts::Tristate::TRUE) ? green :
                (_comp.getValue(1) == nts::Tristate::FALSE) ? red : undef);
    }
}

sf::Sprite & GComponent::getSprite()
{
    return _sprite;
}

GComponent::~GComponent()
{
}

bool GComponent::operator==(const nts::IComponent & comp) const
{
    return &_comp == &comp;
}