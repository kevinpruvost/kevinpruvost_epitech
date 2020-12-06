/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Bullet
*/

#pragma once

#include "Entities/Object/Particle/Particle.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Bullet : public Particle {

        RENTITY_MANDATORIES(Bullet)

        public:
            Bullet(REngine & engine);
            ~Bullet();

            void Start() override;

            const std::string & getSpriteName() {return spriteName;};

        public:
            float _damage = 20;
            std::string spriteName;
            bool ally = true;
            Vector vec;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
