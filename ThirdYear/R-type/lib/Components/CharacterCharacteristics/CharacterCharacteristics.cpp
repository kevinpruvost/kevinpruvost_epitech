/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** CharacterCharacteristics
*/

#include "CharacterCharacteristics.hpp"

using namespace RType::Common::Engine;

CharacterCharacteristics::CharacterCharacteristics(REngine & engine)
    : RComponent(engine)
{
}

CharacterCharacteristics::~CharacterCharacteristics()
{
}

void CharacterCharacteristics::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    _currentHealth = updateRequest.characterisrics._currentHealth;
    _maxHealth = updateRequest.characterisrics._maxHealth;
    _speed = updateRequest.characterisrics._speed;
}