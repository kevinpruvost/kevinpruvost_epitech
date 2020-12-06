/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#include "TitleScreen.hpp"

using namespace RType::Common::Engine;

TitleScreen::TitleScreen(REngine& engine)
    : UIImage(engine)
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Start()
{
    UIImage::Start();

    __transform = GetComponentPtr<UITransform>();

    if (__transform.expired()) return;

    auto transform = __transform.lock();

    transform->size.x = 0.25;
    transform->size.y = 0.1;
    transform->position.x = 0.5;
    transform->position.y = 0.5;
    transform->centered = true;

    __baseSize = transform->size;

    GetComponent<Sprite>().spriteName = "title";
}

void TitleScreen::Update()
{
    if (__transform.expired()) return;

    auto transform = __transform.lock();

    static float time = 0.f;

    time += DeltaTime();

    if (time < 1.f / 144) return;
    time = 0.f;

    if (__sens)
        transform->size *= 1.001;
    else
        transform->size *= 0.999;

    if (transform->size <= __baseSize * 0.75 || transform->size >= __baseSize * 1.5)
        __sens = !__sens;
}