/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Obstacle
*/

#include "Obstacle.hpp"

using namespace RType::Common::Engine;

Obstacle::Obstacle(REngine & engine)
    : Object(engine)
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Start()
{
    AddComponent<Transform>();
    AddComponent<RectangleCollider>();
}
