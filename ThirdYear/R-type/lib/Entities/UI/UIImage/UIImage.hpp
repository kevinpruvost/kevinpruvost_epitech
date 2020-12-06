/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Image
*/

#pragma once

#include "Entities/UI/UI.hpp"
#include "Components/Sprite/Sprite.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class UIImage : public UI {

        RENTITY_MANDATORIES(UIImage)

        public:
            UIImage(REngine & engine);
            ~UIImage();

            void Start() override;

    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
