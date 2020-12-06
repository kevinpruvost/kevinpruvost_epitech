/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** NPC
*/

#pragma once

#include "Entities/Object/Character/Character.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class NPC : public Character {

        RENTITY_MANDATORIES(NPC)

        public:
            NPC(REngine & engine);
            ~NPC();

            void Start() override;            
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
