/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Object
*/

#pragma once

#include "REntity.hpp"
#include "Components/Collider/Collider.hpp"
#include "Components/Collider/RectangleCollider/RectangleCollider.hpp"
#include "Components/Collider/CircleCollider/CircleCollider.hpp"
#include "Components/CharacterCharacteristics/CharacterCharacteristics.hpp"
#include "Components/CharacterCharacteristics/Weapon/Weapon.hpp"
#include "Components/Audio/Audio.hpp"
#include "Components/Sprite/Sprite.hpp"
#include "Components/Sprite/Animation/SpriteAnimation.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Object : public REntity {
    
        RENTITY_MANDATORIES(Object)

        public:
            Object(REngine & engine);
            ~Object();

            void Start() override;

        protected:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType