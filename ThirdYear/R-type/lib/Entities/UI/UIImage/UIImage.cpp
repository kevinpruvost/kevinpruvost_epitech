/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Image
*/

#include "UIImage.hpp"

using namespace RType::Common::Engine;

UIImage::UIImage(REngine & engine)
    : UI (engine)
{
}

UIImage::~UIImage()
{
}

void UIImage::Start()
{
    UI::Start();
    AddComponent<Sprite>();
}

