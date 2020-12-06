/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Character
*/

#include "Character.hpp"

using namespace RType::Common::Engine;

Character::Character(REngine & engine)
    : Object (engine)
{
}

Character::~Character()
{
}

void Character::createBullet()
{
    auto & transform = GetComponent<Transform>();

    auto id = _engine.get().CreateEntity<Bullet>(_engine.get());

    id->spriteName = GetComponent<Weapon>().spriteNameBullet;
    id->ally = GetComponent<Weapon>().ally;
    id->vec = transform.vector;
}

void Character::Start()
{
    AddComponent<Transform>();
    AddComponent<CharacterCharacteristics>();
    AddComponent<Weapon>();
}
