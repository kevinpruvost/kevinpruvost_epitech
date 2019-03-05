/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** Useful to call functions
*/

#ifndef MY_H
#define MY_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef struct framebuffer {
    unsigned char *pixels;
    unsigned int width;
    unsigned int height;
} framebuffer_t;

typedef struct window_prop {
    int width;
    int height;
    float fps;
    sfVector2f scale;
    sfVideoMode mode;
    sfRenderWindow *win;
    framebuffer_t *fb;
    sfEvent event;
    sfMusic *music;
} w_prop;

typedef struct text_obj {
    char *content;
    sfText *text;
    sfFont *font;
    unsigned int chsize;
    sfVector2f pos;
    sfVector2f scale;
} text_obj;

typedef struct sound_obj {
    sfSound *sound;
    sfSoundBuffer *buffer;
} sound_obj;

typedef struct game_obj {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    sfClock *clock;
    sfTime time;
    sfVector2f scale;
} game_obj;

typedef struct player_obj {
    int anim_stade;
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    sfClock *clock_anim;
    sfTime time_anim;
    int jump_mode;
    sfClock *clock_jump;
    sfTime time_jump;
    int y_sol;
    sfVector2f scale;
    sound_obj *death_sound;
} player_obj;

typedef struct background_obj {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    sfClock *clock;
    sfTime time;
    sfVector2f scale;
} bgd_obj;

typedef struct main_menu_vars {
    sfMusic *music;
    bgd_obj *back;
    game_obj *cursor;
    text_obj *button1;
    text_obj *button2;
    int stop;
    int cursor_id;
} mm_vars;

typedef struct map_vars {
    game_obj ***blocks;
    int **id_blocks;
    char **map_char;
    int width;
    int height;
} map_vars;

typedef struct game_vars {
    map_vars *map;
    int stop;
    int alive;
    int pause;
    float speed;
    sfClock *gravity_clock;
    sfClock *death_clock;
    game_obj *pause_txt;
    bgd_obj *back0;
    bgd_obj *back1;
    bgd_obj *back2;
    player_obj *player;
    game_obj *cursor;
    sound_obj *jump_sound;
} gm_vars;

framebuffer_t *framebuffer_create(unsigned int width , unsigned int height);
void put_pixel(unsigned int, unsigned int, sfColor, framebuffer_t *);
void clear_framebuffer(int width, int height, framebuffer_t *fb);
float clock_getseconds(sfClock *clock);

int my_atoi(char *);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
char *my_getnbr(int nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char *load_file_in_mem(char const *filepath);

text_obj *create_text_obj(char *, sfVector2f , sfVector2f pos, sfColor);
void destroy_text_obj(text_obj *text);

sound_obj *create_sound_obj(char *file);
void destroy_sound_obj(sound_obj *snd);
sfMusic *music_create(void);

game_obj *create_game_obj(char *, sfIntRect, sfVector2f pos, sfVector2f);
void destroy_game_obj(game_obj *go_todestroy);

player_obj *create_player_obj(sfVector2f pos, sfVector2f scale);
void destroy_player_obj(player_obj *player);

bgd_obj *create_bgd_obj(char *sprite_file, sfIntRect rect, sfVector2f);
void destroy_bgd_obj(bgd_obj *bgd);

w_prop *create_win_prop(int, int, float);
void destroy_win_prop(w_prop *win);

int game(char **map, w_prop *window);

int main_menu(char **map, w_prop *window);
text_obj *button1_create(sfVector2f scale);
text_obj *button2_create(sfVector2f scale);
game_obj *cursor_create(sfVector2f scale);
bgd_obj *back_create(sfVector2f scale);
bgd_obj *create_image(w_prop *win);
void clear_main_menu(w_prop *win, int *stop);
void draw_main_menu(w_prop *win, mm_vars *mm);
mm_vars *create_mm_vars(w_prop *win);
mm_vars	*destroy_mm_vars_with_music(mm_vars *mm);
mm_vars *destroy_mm_vars_without_music(mm_vars *mm);

gm_vars *create_gm_vars(w_prop *win, char **map);

int my_runner(char *map, char **av);

void destroy_game(gm_vars *gm);
map_vars *map_vars_create(char **map_c, sfVector2f scale);
map_vars *map_vars_create2(char **map_c);

void animation_shrek_walk_jump(gm_vars *gm);
int jump_management(gm_vars *gm, w_prop *win);
int gravity(gm_vars *gm, w_prop *win);
int y_sol_management(gm_vars *gm, w_prop *win);
void analyse_end(gm_vars *gm, w_prop *win);

int pause_delay(gm_vars *gm, w_prop *win);
void scene_movement(gm_vars *gm, w_prop *win);
void cursor_point(gm_vars *gm, w_prop *win);
int move_block(game_obj *block, w_prop *win, gm_vars *gm);
void draw_blocks(gm_vars *gm, w_prop *win);

game_obj *create_block(int mode, sfVector2f scale, int i, int j);
#endif
