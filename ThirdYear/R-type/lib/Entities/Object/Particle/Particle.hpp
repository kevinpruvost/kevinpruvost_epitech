/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Particle
*/

#pragma once

#include "Entities/Object/Object.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Particle : public Object {

        RENTITY_MANDATORIES(Particle)

        public:
            Particle(REngine & engine);
            ~Particle();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
