/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Weapon
*/

#pragma once

#include "lib/Components/CharacterCharacteristics/CharacterCharacteristics.hpp"
//#include "Entities/Object/Particle/Bullet/Bullet.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Weapon : public RComponent {

        RCOMPONENT_MANDATORIES(Weapon)

        public:
            Weapon(REngine & engine);
            ~Weapon();

            //Get
            float getFireRate() const {return _fireRate;};
            float getDamage() const {return _damage;};
            int getProjectileNumber() const {return _projectileNumber;};

            //Set
            void setFireRate(float rate) {_fireRate = rate;}; 
            void setDamage(float damage) {_damage = damage;}; 
            void setProjectileNumber(unsigned int nbr) {_projectileNumber = nbr;};

            void getDamage(int damage, CharacterCharacteristics & character);
            void inflictDamage(int damage, CharacterCharacteristics & character);

            virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

        public:
            float _fireRate = 1.f;
            float _damage = 1.f;
            unsigned int _projectileNumber = 1;
            std::string spriteNameBullet = "boss_projectile";
            bool ally = false;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
