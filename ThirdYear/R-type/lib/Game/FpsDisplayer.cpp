/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#include "FpsDisplayer.hpp"

using namespace RType::Common::Engine;

FpsDisplayer::FpsDisplayer(REngine& engine)
    : UIText(engine)
{
}

FpsDisplayer::~FpsDisplayer()
{
}

void FpsDisplayer::Start()
{
    UIText::Start();

    auto & transform = GetComponent<UITransform>();

    transform.position.x = 0.05;
    transform.position.y = 0.1;
    transform.centered = true;

    __text = GetComponentPtr<Text>();
    
    auto text = __text.lock();
    text->fontName = "default_font";
    text->fontSize = 30;
    text->text = "Jeff";
    text->fontColor = { 0, 255, 0 };
}

void FpsDisplayer::Update()
{
    if (__text.expired()) return;

    static float frames = 0;
    static float totalTime = 0.f;

    if (totalTime >= 2.f)
    {
        totalTime /= 2.f;
        frames /= 2.f;
    }

    ++frames;
    totalTime += DeltaTime();

    auto text = __text.lock();

    text->text = "Fps : " + std::to_string((int)(frames / totalTime));
}