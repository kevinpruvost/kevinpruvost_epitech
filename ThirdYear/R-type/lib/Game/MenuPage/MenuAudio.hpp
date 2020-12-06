/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Audio
*/

#pragma once

#include "Entities/MusicPlayer/MusicPlayer.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class MenuAudio : public MusicPlayer  {

        RENTITY_MANDATORIES(MenuAudio)

        public:
            MenuAudio(REngine & engine);
            ~MenuAudio();

            void Start() override;

        protected:
        private:
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType