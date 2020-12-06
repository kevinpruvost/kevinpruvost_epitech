/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Audio
*/

#pragma once

#include "Engine/RComponent.hpp"

namespace RType
{
namespace Common
{
namespace Engine
{
    class Audio : public RComponent {

        RCOMPONENT_MANDATORIES(Audio)

        public:
            Audio(REngine& engine);
            ~Audio();

            void setPitch(const float pitch);
            void setVolume(unsigned short volume);

            virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

        std::string audioName;
        bool isPlaying = false;
        bool isPaused = false;
        bool isStoped = false;
        bool isLooped = false;
        float pitch = 1.f;
        unsigned short volume = 100;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType