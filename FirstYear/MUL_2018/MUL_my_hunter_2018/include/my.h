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
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct framebuffer {
    unsigned char *pixels;
    unsigned int width;
    unsigned int height;
} framebuffer_t;

framebuffer_t *framebuffer_create(unsigned int width , unsigned int height);
void put_pixel(unsigned int, unsigned int, sfColor, framebuffer_t *);

int my_atoi(char *);
int my_putstr(char *);
int my_strlen(char *);
float my_getfloat(char *toconvert);
char *my_getnbr(int nbr);
char *my_revstr(char *str);
char *str_add(char *base, char *toadd);
char *load_file_in_mem(char const *filepath);

typedef struct window_prop {
    int width;
    int height;
    float fps;
    float scale_x;
    float scale_y;
    sfVector2f scale;
    sfRenderWindow *window;
    framebuffer_t *fb;
    sfEvent event;
} win_prop;

typedef struct sprite_prop {
    sfSprite *sprite;
    sfVector2f position;
} s_prop;

typedef struct duck_prop {
    sfSprite *sprite;
    sfIntRect rect;
    sfVector2f position;
    int sens_h;
    int sens_v;
    float speed;
    sfClock *clock_mov;
    sfClock *clock_anim;
} duck_prop;

typedef struct game_info {
    int AMMO;
    int score;
} game_info;

typedef struct sounds {
    sfMusic *music;
    sfSound *shot;
    sfSoundBuffer *shot_buffer;
} sounds;

typedef struct cross_prop {
    sfVector2f position;
    sfSprite *sprite;
    sfClock *clock;
    sfSound *sound;
} cross_prop;

typedef struct main_prop {
    sfSprite *background;
    sfText *b1;
    sfText *b2;
    int cursor;
} main_menu_content;

typedef struct back_prop {
    sfSprite *background;
    sfSprite *fond;
    sfText *score_text;
} back_prop;

void timer(float);
void move_rect(sfIntRect *rect, int offset, int max_value);
void clear_framebuffer(int, int, framebuffer_t *);
int is_timepassed(sfClock *clock, float seconds_tocheck);
sfSprite *set_background(int width, int height, win_prop *w_prop);
sfSprite *set_background_main_menu(win_prop *);
void manage_keys_pressed(sfVector2f *pos);
void manage_mouse_click(sfMouseButtonEvent event);
void analyse_events(sfEvent event, sfVector2f *pos);
sfSprite *set_fond(int width, int height, win_prop *w_prop);
sfVector2f duck_movements(duck_prop *duck, win_prop *w_prop);
sfSprite *set_crosshair(int width, int height, win_prop *w_prop);
sfSprite *set_duck(int width, int height, win_prop *w_prop);
sfVector2f move_crosshair(sfVector2f, sfSprite *, sfRenderWindow *window);
sfVector2f shoot(cross_prop, win_prop *, game_info *, duck_prop *duck);
int direction_change(int direction);
sfText *button1_creation(sfText *score, int width, int height);
sfText *button2_creation(sfText *score, int width, int height);
void music_launching(sounds *);
int main_menu(win_prop *w_prop, sounds *sounds_prop, game_info *game_infos);
void render_ammo(win_prop *w_prop, game_info *game_infos);
void shooting_sound(sfSound *sound, sfClock *clock);
sfText *scoretext_creation(sfText *score, int width, int height);

void reset_game(game_info *game_infos);
void end_window(win_prop *w_prop, sounds *sounds_prop);
int main_menu_window(main_menu_content *mm_content, win_prop *w_prop);
void end_my_duck(sfSprite *sprite, win_prop *w_prop, sounds *, game_info *);

void cursor_managing(int *cursor);
sfText *button1_creation(sfText *score, int width, int height);
sfText *button2_creation(sfText *score, int width, int height);
void manage_button_1(sfText **button, int *cursor, sfRenderWindow *);
void manage_button_2(sfText **button, int *cursor, sfRenderWindow *);

win_prop set_w_prop(win_prop w_prop, int wi, int he, float ips);
duck_prop set_duck_props(duck_prop duck, win_prop *w_prop);
cross_prop set_cross_props(cross_prop crosshair, win_prop *w_prop, sounds *);

back_prop set_background_props(back_prop back, win_prop *w_prop);
void check_clean_window(win_prop *w_prop, game_info *game_infos, int *);
void render_window(win_prop *, back_prop, duck_prop, game_info *);
void data_change(win_prop *w_prop, duck_prop *dk, cross_prop *cr, game_info *);

#endif
