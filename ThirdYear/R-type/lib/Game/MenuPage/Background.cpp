/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Background
*/

#include "Background.hpp"

using namespace RType::Common::Engine;

Background::Background(REngine & engine)
    : REntity (engine)
{
}

Background::~Background()
{
}

void Background::Start()
{
    AddComponent<Transform>();
    AddComponent<Sprite>();

    auto & transform = GetComponent<Transform>();

    transform.isStatic = false;
    transform.vector.size.x = 3840;
    transform.vector.size.y = 1080;
    transform.vector.position.x = -1920;
    transform.vector.position.y = 0;

    GetComponent<Sprite>().spriteName = "background";
}

void Background::Update()
{
    auto& transform = GetComponent<Transform>();
    if (transform.vector.position.x >= 0)
        transform.vector.position.x = -1920;
    transform.MoveTo(0, 0, 100);
}