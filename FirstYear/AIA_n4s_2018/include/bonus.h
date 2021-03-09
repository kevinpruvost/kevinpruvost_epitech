/*
** EPITECH PROJECT, 2019
** bonus.h
** File description:
** bonus header
*/

#ifndef BONUS_H
#define BONUS_H

#include "my.h"
#include "csfml.h"

typedef struct window_s {
    sfRenderWindow *win;
    sfVideoMode mode;
    sfClock *clock;
    sfEvent event;
    obj_t *cursor;
    obj_t *keys[4];
    obj_t *stop;
    obj_t *bgd;
    obj_t *exit_button;
    sfText *speed;
    sfText *rotation;
} window_t;

char *my_getnbr(int nbr);

int help_option(char **av, int n);

void sprite_set_origin(sfSprite *sprite, float x, float y);

void edit_text(sfText *t, char *str, float x, float y);
sfText *create_text(char *str, int size, sfFont *font);
void edit_text_str(sfText *t, char *str);

window_t *create_window_t(ai_t *w);
void destroy_window_t(window_t *b);

int render_game(window_t *b, ai_t *w);
int actions_and_events(window_t *b, ai_t *w);

void actions_and_events_keys(window_t *b, ai_t *w);
void turn_car(window_t *b, ai_t *w, float nb);
int move_forward_car(window_t *b, ai_t *w, float nb);
int move_backwards_car(window_t *b, ai_t *w, float nb);

int cut_animation(obj_t *obj, int x, int y);
int anim_sprite(obj_t *obj, int sens, int ite);

#endif
