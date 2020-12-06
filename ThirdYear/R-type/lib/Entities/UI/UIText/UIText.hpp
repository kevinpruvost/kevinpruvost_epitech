/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Text
*/

#pragma once

#include "Entities/UI/UI.hpp"
#include "Components/Text/Text.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class UIText : public UI {
            
        RENTITY_MANDATORIES(UIText)

        public:
            UIText(REngine & engine);
            ~UIText();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
