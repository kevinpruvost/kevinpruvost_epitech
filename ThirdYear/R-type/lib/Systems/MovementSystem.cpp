/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MovementSystem
*/

#include "MovementSystem.hpp"

using namespace RType::Common::Engine;

MovementSystem::MovementSystem(REngine & engine)
    : RSystem(engine)
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Start()
{
    AddComponentSignature<Transform>();
}

void MovementSystem::TickByEntity(REntity & entity)
{
    auto & transform = entity.GetComponent<Transform>();
    auto direction = transform.vector.GetDirection();
    float speed = transform.vector.GetSpeed();
    float time = DeltaTime();
    auto position = transform.vector.position;

    if (transform.isStatic) return;
    
    if (speed <= 0.f || position == direction)
    {
        return;
    }

    auto distance = position.Distance(direction);
    auto distanceToGo = speed * time;

    auto totalMove = position - direction;

    auto ratio = (distanceToGo > distance) ? 1 : distanceToGo / distance;

    auto newPos = position - (totalMove * ratio);

    transform.hasMoved = true;

    transform.vector.position = newPos;
}

