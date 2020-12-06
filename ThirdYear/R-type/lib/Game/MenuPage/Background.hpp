/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Background
*/

#pragma once

// Project includes
#include "Engine/REntity.hpp"
#include "Entities/UI/UIImage/UIImage.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Background : public REntity
    {

        RENTITY_MANDATORIES(Background)

        public:
            Background(REngine & engine);
            ~Background();

            void Start() override;
            void Update() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType