/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Button
*/

#include "UIButton.hpp"

using namespace RType::Common::Engine;

UIButton::UIButton(REngine & engine)
    : UI (engine)
{
}

UIButton::~UIButton()
{
}

void UIButton::Start()
{
    UI::Start();
    AddComponent<Button>();
    AddComponent<Sprite>();
    AddComponent<SpriteAnimation>();

    GetComponent<SpriteAnimation>().animationLooped = false;
}

void UIButton::Update()
{
    if (GetComponent<Button>()._isHover)
            GetComponent<SpriteAnimation>().startAnimationLoop();
    GetComponent<SpriteAnimation>().stopAndResetAnimation();
}
