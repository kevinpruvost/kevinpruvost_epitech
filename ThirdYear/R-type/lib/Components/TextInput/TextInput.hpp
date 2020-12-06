/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextInput
*/

#pragma once

#include "Engine/RComponent.hpp"
#include "Components/Text/Text.hpp"
#include "Network/Rfc.hpp"
#include "Components/KeyInput/KeyInput.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class TextInput : public RComponent {

        RCOMPONENT_MANDATORIES(TextInput)

        public:
            TextInput(REngine & engine);
            ~TextInput();

            void addCharacter(const char charac);
            void addString(const std::string & str);
            void addKeyInput();

            void deleteLastCharacter();
            void deleteLastXCharacter(unsigned int x);

            void linkToKeyInput();

            virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

            bool capslock = false;
            int cursor = 0;
            unsigned int maxSize = 7;
            std::function<void()> callbackOnEnter;
        };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType