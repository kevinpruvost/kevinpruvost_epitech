/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextRoom
*/

#pragma once

#include "Engine/REntity.hpp"
#include "Entities/UI/UIText/UIText.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class TextRoom : public UIText {

        RENTITY_MANDATORIES(TextRoom)

        public:
            TextRoom(REngine & engine);
            ~TextRoom();

            void Start() override;

        private:
            std::weak_ptr<UITransform> __transform;
    };
};
};
};
