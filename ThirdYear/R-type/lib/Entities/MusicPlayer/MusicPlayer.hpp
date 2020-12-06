/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MusicPlayer
*/

#pragma once

#include "REntity.hpp"
#include "Components/Audio/Audio.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class MusicPlayer : public REntity {

        RENTITY_MANDATORIES(MusicPlayer)

        public:
            MusicPlayer(REngine & engine);
            ~MusicPlayer();

            void Start() override;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType