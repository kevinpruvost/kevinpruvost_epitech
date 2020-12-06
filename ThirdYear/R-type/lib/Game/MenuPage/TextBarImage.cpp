/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextBarImage
*/

#include "TextBarImage.hpp"

using namespace RType::Common::Engine;

TextBarImage::TextBarImage(REngine & engine)
    : UIImage(engine)
{
}

TextBarImage::~TextBarImage()
{
}

void TextBarImage::Start()
{
    UIImage::Start();

    __transform = GetComponentPtr<UITransform>();

    if (__transform.expired()) return;

    auto transform = __transform.lock();

    transform->size.x = 0.25;
    transform->size.y = 0.1;
    transform->position.x = 0.5;
    transform->position.y = 0.7;
    transform->centered = true;

    GetComponent<Sprite>().spriteName = "button";
}
