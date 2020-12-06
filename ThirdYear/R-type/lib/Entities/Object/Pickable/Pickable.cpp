/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Pickable
*/

#include "Pickable.hpp"

using namespace RType::Common::Engine;

Pickable::Pickable(REngine & engine)
    : Object(engine)
{
}

Pickable::~Pickable()
{
}

void Pickable::Start()
{
    AddComponent<RectangleCollider>();
    AddComponent<Transform>();
}