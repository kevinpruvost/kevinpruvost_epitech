/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameBoss
*/

#pragma once

#include "Entities/Object/Character/NonPlayerCharacter/Enemy/Enemy.hpp"

#include <array>

namespace RType
{
namespace Common
{
namespace Engine
{
    class InGameBoss : public Enemy
    {
        RENTITY_MANDATORIES(InGameBoss)
    
    public:
        InGameBoss(REngine & engine);
        ~InGameBoss();

        void Start() override;
        void Update() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType