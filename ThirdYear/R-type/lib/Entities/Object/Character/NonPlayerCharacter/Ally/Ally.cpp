/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Ally
*/

#include "Ally.hpp"

using namespace RType::Common::Engine;

Ally::Ally(REngine & engine)
    : NPC (engine)
{
    _isAlly = true;
}

Ally::~Ally()
{
}

void Ally::Start()
{
    AddComponent<CircleCollider>();
    AddComponent<Transform>();
    AddComponent<CharacterCharacteristics>();
    AddComponent<Weapon>();
    AddComponent<Audio>();
    AddComponent<Sprite>();
    AddComponent<SpriteAnimation>();
}