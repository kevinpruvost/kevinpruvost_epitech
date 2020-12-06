/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** Audio
*/

#include "MenuAudio.hpp"

using namespace RType::Common::Engine;

MenuAudio::MenuAudio(REngine & engine)
    : MusicPlayer (engine)
{
}

MenuAudio::~MenuAudio()
{
}

void MenuAudio::Start()
{
    MusicPlayer::Start();

    auto & audio = GetComponent<Audio>();
    audio.audioName = "music";
    audio.isLooped = true;
    audio.isPlaying = true;
}
