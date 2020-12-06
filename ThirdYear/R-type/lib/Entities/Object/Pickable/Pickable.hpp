/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Pickable
*/

#pragma once

#include "Entities/Object/Object.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Pickable : public Object {
    
        RENTITY_MANDATORIES(Pickable)

        public:
            Pickable(REngine & engine);
            ~Pickable();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType