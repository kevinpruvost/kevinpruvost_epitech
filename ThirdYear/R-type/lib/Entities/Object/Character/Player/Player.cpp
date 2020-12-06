/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Player
*/

#include "Player.hpp"

using namespace RType::Common::Engine;

Player::Player(REngine & engine)
    : Character (engine)
{
    _isAlly = true;
}

Player::~Player()
{
}

void Player::Start()
{
    AddComponent<RectangleCollider>();
    AddComponent<Transform>();
    AddComponent<CharacterCharacteristics>();
    AddComponent<Weapon>();
    AddComponent<Audio>();
    AddComponent<Sprite>();
    AddComponent<SpriteAnimation>();
}
