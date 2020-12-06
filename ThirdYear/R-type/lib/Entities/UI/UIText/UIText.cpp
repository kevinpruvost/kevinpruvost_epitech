/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Text
*/

#include "UIText.hpp"

using namespace RType::Common::Engine;

UIText::UIText(REngine & engine)
    : UI (engine)
{
}

UIText::~UIText()
{
}

void UIText::Start()
{
    UI::Start();
    AddComponent<Text>();
}
