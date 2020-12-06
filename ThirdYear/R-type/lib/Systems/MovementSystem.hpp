/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MovementSystem
*/

#pragma once

#include "Engine/RSystem.hpp"
#include "Components/Transform/Transform.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class MovementSystem : virtual public RSystem {
        public:
            MovementSystem(REngine & engine);
            ~MovementSystem();

            void Start() override;
            void TickByEntity(REntity & entity) override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType