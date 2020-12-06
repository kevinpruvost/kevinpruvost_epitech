/*
** EPITECH PROJECT, 2018
** sound_obj.c
** File description:
** sound func
*/

#include "my.h"

sound_obj *create_sound_obj(char *file)
{
    sound_obj *snd = malloc(sizeof(sound_obj));

    snd->sound = sfSound_create();
    snd->buffer = sfSoundBuffer_createFromFile(file);
    sfSound_setBuffer(snd->sound, snd->buffer);
    sfSound_setVolume(snd->sound, 30);
    return (snd);
}

void destroy_sound_obj(sound_obj *snd)
{
    sfSoundBuffer_destroy(snd->buffer);
    sfSound_destroy(snd->sound);
    free(snd);
}

sfMusic *music_create(void)
{
    sfMusic *music = sfMusic_createFromFile("sounds/all_star.ogg");

    sfMusic_setVolume(music, 5);
    return (music);
}
