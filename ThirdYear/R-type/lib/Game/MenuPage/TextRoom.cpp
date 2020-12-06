/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextRoom
*/

#include "TextRoom.hpp"

using namespace RType::Common::Engine;

TextRoom::TextRoom(REngine & engine)
    : UIText (engine)
{
}

TextRoom::~TextRoom()
{
}

void TextRoom::Start()
{
    UIText::Start();

    __transform = GetComponentPtr<UITransform>();

    if (__transform.expired()) return;

    auto transform = __transform.lock();

    auto& text = GetComponent<Text>();
    text.fontName = "default_font";
    text.fontSize = 15;
    text.fontColor = { 0, 255, 0 };
    text.text = "Enter the room's id that you wanna join/create";

    transform->position.x = 0.5 - ((0.006 * text.text.size()) / 2);
    transform->position.y = 0.775;

}
