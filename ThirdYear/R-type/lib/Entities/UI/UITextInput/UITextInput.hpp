/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UITextInput
*/

#pragma once

#include "lib/Entities/UI/UI.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class UITextInput : public UI {

        RENTITY_MANDATORIES(UITextInput)

        public:
            UITextInput(REngine & engine);
            ~UITextInput();

            void Start() override;

    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType