/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Weapon
*/

#include "Weapon.hpp"

using namespace RType::Common::Engine;

Weapon::Weapon(REngine & engine)
    : RComponent(engine)
{
}

Weapon::~Weapon()
{
}

void Weapon::getDamage(int damage, CharacterCharacteristics & character)
{
    int health = character.getCurrentHealth();

    health - damage > 0 ? character.setCurrentHealth(health - damage) : \
    character.setCurrentHealth(0);
}

void Weapon::inflictDamage(int damage, CharacterCharacteristics & character)
{
    getDamage(damage, character);
}

void Weapon::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    _fireRate = updateRequest.weapon._fireRate;
    _damage = updateRequest.weapon._damage;
    _projectileNumber = updateRequest.weapon._projectileNumber;
    spriteNameBullet = updateRequest.weapon.spriteNameBullet;
    ally = updateRequest.weapon.ally;
}
