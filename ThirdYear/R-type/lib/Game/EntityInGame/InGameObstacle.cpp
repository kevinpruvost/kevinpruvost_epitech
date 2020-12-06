/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameObstacle
*/

#include "InGameObstacle.hpp"

using namespace RType::Common::Engine;

InGameObstacle::InGameObstacle(REngine & engine)
    : Obstacle (engine)
{
}

InGameObstacle::~InGameObstacle()
{
}

void InGameObstacle::Start()
{
    Obstacle::Start();
    auto & transform = GetComponent<Transform>();

    transform.isStatic = true;

    GetComponent<RectangleCollider>().colliderLayer = Engine::ColliderLayer::Obstacle;
    
    transform.vector = _vector;
}

void InGameObstacle::SetToLeft()
{
    _vector.position.x = -12;
    _vector.size.x = 10;
    _vector.size.y = 1080;
}

void InGameObstacle::SetToRight()
{
    _vector.position.x = 2500;
    _vector.size.x = 10;
    _vector.size.y = 1080;
}

void InGameObstacle::SetToUp()
{
    _vector.position.y = -10;
    _vector.size.x = 1980;
    _vector.size.y = 10;
}

void InGameObstacle::SetToDown()
{
    _vector.position.y = 1090;
    _vector.size.x = 1980;
    _vector.size.y = 10;
}

