/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Enemy
*/

#pragma once

#include "Entities/Object/Character/NonPlayerCharacter/NPC.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Enemy : public NPC {

        RENTITY_MANDATORIES(Enemy)

        public:
            Enemy(REngine & engine);
            ~Enemy();

            void Start() override;

        protected:
        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
