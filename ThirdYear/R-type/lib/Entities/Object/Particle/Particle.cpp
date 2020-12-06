/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Particle
*/

#include "Particle.hpp"

using namespace RType::Common::Engine;

Particle::Particle(REngine & engine)
    : Object(engine)
{
}

Particle::~Particle()
{
}

void Particle::Start()
{
    AddComponent<CircleCollider>();
    AddComponent<Transform>();
}