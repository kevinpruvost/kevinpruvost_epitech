/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** UI
*/

#pragma once

#include "REntity.hpp"
#include "Components/UITransform/UITransform.hpp"
#include "Components/Sprite/Animation/SpriteAnimation.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Components/Button/Button.hpp"
#include "Components/TextInput/TextInput.hpp"
#include "Components/KeyInput/KeyInput.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class UI : public REntity {

        RENTITY_MANDATORIES(UI)

        public:
            UI(REngine & engine);
            ~UI();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType