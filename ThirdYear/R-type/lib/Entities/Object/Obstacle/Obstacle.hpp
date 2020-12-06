/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Obstacle
*/

#pragma once

#include "Entities/Object/Object.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Obstacle : public Object {

        RENTITY_MANDATORIES(Obstacle)

        public:
            Obstacle(REngine & engine);
            ~Obstacle();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType