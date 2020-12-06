/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#include "Object.hpp"

using namespace RType::Common::Engine;

Object::Object(REngine & engine)
    : REntity(engine)
{
}

Object::~Object()
{
}

void Object::Start()
{
    AddComponent<Transform>();
}