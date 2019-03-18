/*
** EPITECH PROJECT, 2019
** obj.h
** File description:
** struct for objs
*/

#ifndef OBJ_H
#define OBJ_H

#include "libs.h"

typedef struct time_obj {
    sfTime time;
    float seconds_init;
    float seconds;
} time_obj;
time_obj *create_time_obj(sfClock *clock);
void reset_time(time_obj *time, sfClock *clock);
float get_time(time_obj *time, sfClock *clock);
void destroy_time_obj(time_obj *time);
void end_pause_time(time_obj *time, sfClock *clock);

typedef struct text_obj {
    char *content;
    sfText *text;
    sfFont *font;
    unsigned int chsize;
    sfVector2f pos;
    sfVector2f scale;
} text_obj;
text_obj *create_text_obj(char *txt, sfVector2f sc, sfVector2f pos, sfColor c);
void destroy_text_obj(text_obj *text);

typedef struct sound_obj {
    sfSound *sound;
    sfSoundBuffer *buffer;
} sound_obj;
sound_obj *create_sound_obj(char *file);
void destroy_sound_obj(sound_obj *snd);

typedef struct game_obj {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfVector2f origin;
    sfIntRect rect;
    time_obj *time_move;
    time_obj *time_anim;
    sfVector2f scale;
    sfColor color;
} game_obj;
game_obj *create_game_obj(char *f, sfIntRect r, sfVector2f posi, sfClock *c);
void destroy_game_obj(game_obj *go_todestroy);
void destroy_bars(game_obj **bar);

typedef struct player_obj {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    sfTime time_anim;
    sfVector2f scale;
} player_obj;

typedef struct background_obj {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    sfTime time;
    sfVector2f scale;
} bgd_obj;
bgd_obj *create_bgd_obj(char *sprite_file, sfIntRect rect, sfVector2f scale);
void destroy_bgd_obj(bgd_obj *bgd);

#endif
