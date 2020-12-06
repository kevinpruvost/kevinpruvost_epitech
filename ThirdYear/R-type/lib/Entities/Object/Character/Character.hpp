/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Character
*/

#pragma once

#include "Entities/Object/Object.hpp"
#include "Components/CharacterCharacteristics/CharacterCharacteristics.hpp"
#include "Systems/MovementSystem.hpp"
#include "Entities/Object/Particle/Bullet/Bullet.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Character : public Object {

        RENTITY_MANDATORIES(Character)

        public:
            Character(REngine & engine);
            ~Character();

            void Start() override;

            void createBullet();
            const bool getIsAlly() { return _isAlly;};

        protected:
            bool _isAlly;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType