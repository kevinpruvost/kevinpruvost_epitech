/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Player
*/

#pragma once

#include "Entities/Object/Character/Character.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Player : public Character {

        RENTITY_MANDATORIES(Player)

        public:
            Player(REngine & engine);
            ~Player();

            void Start() override;

        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
