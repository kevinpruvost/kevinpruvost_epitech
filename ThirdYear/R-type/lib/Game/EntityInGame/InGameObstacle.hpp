/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** InGameObstacle
*/

#pragma once

#include "Entities/Object/Obstacle/Obstacle.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class InGameObstacle : public Obstacle {

        RENTITY_MANDATORIES(InGameObstacle)

        public:
            InGameObstacle(REngine & engine);
            ~InGameObstacle();

            void SetToRight();
            void SetToUp();
            void SetToDown();
            void SetToLeft();

            void Start() override;
        
        private:
            Vector _vector;

    };
};
};
};
