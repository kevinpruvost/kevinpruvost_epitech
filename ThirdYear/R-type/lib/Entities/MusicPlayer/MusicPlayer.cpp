/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** MusicPlayer
*/

#include "MusicPlayer.hpp"

using namespace RType::Common::Engine;

MusicPlayer::MusicPlayer(REngine & engine)
    : REntity (engine)
{
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::Start()
{
    AddComponent<Audio>();
}
