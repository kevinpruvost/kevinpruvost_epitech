/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameGenericMob
*/

#pragma once

#include "Entities/Object/Character/NonPlayerCharacter/Enemy/Enemy.hpp"

#include <array>

namespace RType
{
namespace Common
{
namespace Engine
{
    class InGameGenericMob : public Enemy {

        RENTITY_MANDATORIES(InGameGenericMob)

        public:
            InGameGenericMob(REngine & engine);
            ~InGameGenericMob();

            void Start() override;
            void Update() override;

        protected:
        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
