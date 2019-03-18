/*
** EPITECH PROJECT, 2018
** my_struct
** File description:
** my_struct_defender
*/

#ifndef MUL_MY_DEFENDER_2018_MY_H
#define MUL_MY_DEFENDER_2018_MY_H

#include "../lib/get_next_line.h"
#include "libs.h"
#include "struct.h"
#include "lvl.h"

int my_atoi(char *);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
char *my_getnbr(int nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char *load_file_in_mem(char const *filepath);
int is_str(char *, char *);
char *float_to_s(float nb);
int is_env_display(char **env);

typedef struct radius_coll {
    float radius;
    float rx;
    float ry;
    float x1;
    float y1;
    float x2;
    float y2;
} radius_coll;

void mod_scale(sfSprite *sprite, float n);
int is_left_click(sfEvent event, game_obj *obj1, game_obj *obj2);
float clock_getseconds(sfClock *clock);
void window_check(sfRenderWindow *win);
sfBool is_button_released(sfMouseButton, sfRenderWindow *);
void set_visible(sfSprite *sprite);
void set_invisible(sfSprite *sprite);
void mod_color(sfSprite *sprite, float re, float gr, float bl);
void center_game_object(game_obj *game_obj);
void center_mob(game_obj *game_obj);
void center_hp(game_obj *hp, game_obj *obj2);
int is_in_radius(game_obj *obj1, game_obj *obj2, float radius);
int anim_sprite(game_obj *obj, int anim_count);

void events_main_menu(game_s *game);
void animation_bgd(game_s *game);

void draw_main_menu(game_s *game);
void event_main_menu(game_s *game);

void draw_htp(game_s *game);
void event_htp(game_s *game);

void draw_lvl(game_s *game);
void event_lvl(game_s *game);

void draw_settings(game_s *game);
void event_settings(game_s *game);

void draw_map_editor(game_s *game);
void event_map_editor(game_s *game);

funcs_game_t *create_main_funcs(void);

void destroy(game_s *game, funcs_game_t *funcs);

void get_score(int scores[3]);
void write_score(int scores[3]);
void add_new_score(game_s *game);
void actualize_score(game_s *game);

#endif //MUL_MY_DEFENDER_2018_MY_H
