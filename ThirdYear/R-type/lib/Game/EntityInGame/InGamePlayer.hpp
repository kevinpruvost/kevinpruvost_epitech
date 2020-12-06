/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Player
*/

#pragma once

#include "Entities/Object/Character/Player/Player.hpp"
#include "Entities/Object/Particle/Bullet/Bullet.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class InGamePlayer : public Player {

        RENTITY_MANDATORIES(InGamePlayer)

        public:
            InGamePlayer(REngine & engine);
            ~InGamePlayer();

            void Start() override;
            void ChangeColorSprite(SpriteColor spriteColor);

            void Input(Rfc::InputCode key);
            void Update() override;

        private:
            void Shoot();
            void MoveToLeft();
            void MoveToRight();
            void MoveDown();
            void MoveUp();
    };
};
};
};