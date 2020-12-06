/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Button
*/

#pragma once

#include "Engine/RComponent.hpp"
#include <functional>

namespace RType
{
namespace Common
{
namespace Engine
{
    class Button : public RComponent {

        RCOMPONENT_MANDATORIES(Button)

        public:
            Button(REngine & engine);
            ~Button();

            void hasBeenPressed();
            void setCallback(const std::function<void ()> function);

            virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

            bool _isHover = false;
            std::function<void ()> __callbackFunction;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
