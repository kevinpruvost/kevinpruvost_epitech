/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Ally
*/

#pragma once

#include "Entities/Object/Character/NonPlayerCharacter/NPC.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Ally : public NPC {

        RENTITY_MANDATORIES(Ally)

        public:
            Ally(REngine & engine);
            ~Ally();

            void Start() override;

        protected:
        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType