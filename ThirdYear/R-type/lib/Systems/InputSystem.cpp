/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InputSystem
*/

#include "InputSystem.hpp"

using namespace RType::Common::Engine;

InputSystem::InputSystem(REngine & engine)
    : RSystem (engine)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Start()
{
    AddComponentSignature<KeyInput>();
}

void InputSystem::Update()
{
}

void InputSystem::Tick()
{
}

void TickByEntity(REntity & entity)
{
    auto & input = entity.GetComponent<KeyInput>();
    RType::Common::Rfc::InputCode code = input.inputCode;

    if (input.callback)
        input.callback();
}

