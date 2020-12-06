/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Audio
*/

#include "Audio.hpp"

using namespace RType::Common::Engine;

Audio::Audio(REngine & engine)
    : RComponent(engine)
{
}

Audio::~Audio()
{
}

void Audio::setPitch(const float pitc)
{
    pitch = pitc;
}

void Audio::setVolume(unsigned short volum)
{
    volume = volum;

    if (volume > 100)
        volume = 100;
}

void Audio::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    audioName = updateRequest.audio.audioName;
    isLooped = updateRequest.audio.isLooped;
    isPlaying = updateRequest.audio.isPlaying;
    isPaused = updateRequest.audio.isPaused;
    isStoped = updateRequest.audio.isStoped;
    pitch = updateRequest.audio.pitch;
    volume = updateRequest.audio.volume;
}