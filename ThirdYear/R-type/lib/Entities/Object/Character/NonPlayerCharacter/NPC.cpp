/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** NPC
*/

#include "NPC.hpp"

using namespace RType::Common::Engine;

NPC::NPC(REngine & engine)
    : Character (engine)
{
}

NPC::~NPC()
{
}

void NPC::Start()
{
    AddComponent<CircleCollider>();
    AddComponent<Transform>();
    AddComponent<CharacterCharacteristics>();
    AddComponent<Weapon>();
    AddComponent<Audio>();
    AddComponent<Sprite>();
    AddComponent<SpriteAnimation>();
}