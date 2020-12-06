/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Button
*/

#pragma once

#include "Entities/UI/UI.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class UIButton : public UI {

        RENTITY_MANDATORIES(UIButton)

        public:
            UIButton(REngine & engine);
            ~UIButton();

            void Start() override;
            void Update() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType