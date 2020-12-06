/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** TextBarImage
*/

#pragma once

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
    class TextBarImage : public UIImage {

        RENTITY_MANDATORIES(TextBarImage)

        public:
            TextBarImage(REngine & engine);
            ~TextBarImage();

            void Start() override;

        private:
            std::weak_ptr<UITransform> __transform;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType