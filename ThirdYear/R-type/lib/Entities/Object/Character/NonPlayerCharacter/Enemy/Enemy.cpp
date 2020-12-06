/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Enemy
*/

#include "Enemy.hpp"

using namespace RType::Common::Engine;

Enemy::Enemy(REngine & engine)
    : NPC (engine)
{
    _isAlly = false;
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
    AddComponent<RectangleCollider>();
    AddComponent<Transform>();
    AddComponent<CharacterCharacteristics>();
    AddComponent<Weapon>();
    AddComponent<Audio>();
    AddComponent<Sprite>();
    AddComponent<SpriteAnimation>();
}