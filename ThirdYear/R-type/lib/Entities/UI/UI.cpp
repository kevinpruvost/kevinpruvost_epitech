/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UI
*/

#include "UI.hpp"

using namespace RType::Common::Engine;

UI::UI(REngine & engine)
    : REntity (engine)
{
}

UI::~UI()
{
}

void UI::Start()
{
    AddComponent<UITransform>();
}
