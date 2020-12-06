/*
** EPITECH PROJECT, 2018
** my_struct
** File description:
** my_struct_defender
*/

#ifndef STRUCT_H
#define STRUCT_H

#include "obj.h"
#include "libs.h"

#define WIN_NAME "Shrek Tower Defense"

typedef enum page
{
    MAINMENU,
    LEVEL,
    HTP,
    MAP_EDITOR,
    SETTINGS
} page_t;

typedef struct s_menu {
    bgd_obj *background;
    game_obj *sprite_bgd;
    game_obj *play_button;
    game_obj *htp_button;
    game_obj *quit_button;
    game_obj *map_editor_button;
    game_obj *settings_button;
    text_obj *ranks[3];
    game_obj *cursor;
} menu_s;
menu_s *create_menu_s(sfClock *);
game_obj *create_sprite_bgd(sfClock *);
game_obj *create_cursor(sfClock *);
game_obj *create_play_button(sfClock *);
game_obj *create_htp_button(sfClock *);
game_obj *create_quit_button(sfClock *);
game_obj *create_map_editor_button(sfClock *);
game_obj *create_settings_button(sfClock *);
game_obj *create_clear_button(sfClock *);
game_obj *create_random_button(sfClock *);
game_obj *create_remove_button(sfClock *);
game_obj *create_remove_desc(sfClock *);
game_obj *create_clear_desc(sfClock *);
game_obj *create_random_desc(sfClock *);
game_obj *create_not_valid(sfClock *clock);
game_obj *create_return_desc(sfClock *clock);

void destroy_menu_s(menu_s *mm_vars);
menu_s *change_menu_s(menu_s *mm_vars, sfClock *clock);

typedef	struct htp_s {
    sfClock *clock;
    sfVideoMode mode;
    sfRenderWindow *window;
    bgd_obj *background;
    game_obj *button;
    game_obj *cursor;
    sfMusic *music;
} htp_s;
htp_s *create_htp_s(sfClock *clock);
void destroy_htp_s(htp_s *htp_vars);
htp_s *change_htp_s(htp_s *htp_vars, sfClock *clock);
game_obj *create_htp_return_button(sfClock *clock);

typedef struct settings_s {
    bgd_obj *background;
    game_obj *cursor;
    int pause;
    float music_volume;
    float sound_volume;
    game_obj *music_button;
    game_obj *sound_button;
    game_obj **music_bar;
    game_obj **sound_bar;
    game_obj *return_button;
} settings_s;
settings_s *create_settings_s(sfClock *);
void destroy_settings_s(settings_s *);
game_obj **create_music_bar(sfClock *clock);
game_obj **create_sound_bar(sfClock *clock);
game_obj *create_return_button_sett(sfClock *clock);

typedef struct map_editor_s {
    bgd_obj *background;
    bgd_obj *grid;
    game_obj *cursor;
    game_obj *p_cases[10][6];
    int pause;
    game_obj *return_button;
    game_obj *clear_button;
    game_obj *random_button;
    game_obj *remove_button;
    game_obj *clear_desc;
    game_obj *random_desc;
    game_obj *remove_desc;
    game_obj *return_desc;
    game_obj *not_valid;
} map_editor_s;
map_editor_s *create_map_editor_s(sfClock *);
void destroy_map_editor_s(map_editor_s *);

#include "game.h"

typedef enum sounds_list {
    DEATH,
    DRAGON,
    SFD,
    NWAVE,
    DEATH1,
    DEATH2
} sound_list;

typedef struct s_game {
    sfRenderWindow *win;
    page_t old_page;
    page_t page;
    sfClock *clock;
    menu_s *mm_vars;
    lvl_s *lvl_vars;
    htp_s *htp_vars;
    map_editor_s *maped_vars;
    settings_s *sett_vars;
    sfMusic *music;
    sfMusic *beep;
    sfMusic *sound_fx[6];
    int score;
    map_t *map;
    int scores[3];
    game_obj *range[2];
    game_obj *start_button;
    int start;
} game_s;
game_s *create_game_s(void);
void destroy_game_s(game_s *game);

void change_page_back(game_s *game);
void change_page(game_s *game, int page);

typedef struct main_funcs {
    void (*draws[5])(game_s *);
    void (*events[5])(game_s *);
    void (*changes[5])(game_s *);
} funcs_game_t;

int collision_cursor(game_obj *cursor, game_obj *obj);
int collision_entities(game_obj *obj1, game_obj *obj2);

void display_tower_info(game_s *game);

bgd_obj *create_grid(void);
game_obj *create_cursor(sfClock *);

void event_main_menu_mod_buttons(game_s *game);
void events_main_menu(game_s *game);
void event_main_menu_set_buttons(game_s *game);

int is_map_finished(game_s *game);
void show_p_cases(game_s *game);
int check_valid_case(game_obj *cases);
void add_case(game_s *game, int x, int y);
int playable_map(game_s *game);
void remove_case(game_s *game);
void event_buttons_map_editor_1(game_s *game);
void event_buttons_map_editor_2(game_s *game);
void event_buttons_map_editor_3(game_s *game, sfEvent event);
void event_buttons_map_editor_4(game_s *game, sfEvent event);
void draw_map_editor1(game_s *game);
void draw_map_editor2(game_s *game);

void add_new_tower(game_s *game, int id, sfVector2f pos);
void destroy_tower(tower_t *towers, tower_t *tower_to_kill);
tower_t *create_towers(void);
void destroy_towers(tower_t *towers);
void add_new_mob(game_s *game, int id, int wave);
void kill_mob(mob_t *mobs, mob_t *mob_to_kill);
mob_t *create_mobs(void);
void destroy_mobs(mob_t *mobs);
void add_new_proj(game_s *game, tower_t *tow, mob_t *mob);
void destroy_proj(proj_t *projs, proj_t *proj_to_kill);
proj_t *create_projs(void);
void destroy_projs(proj_t *projs);

void event_settings2(game_s *game);
void set_alpha_sett_bars(game_s *game);

void pause_resume(game_s *game);

void spawn_mobs(game_s *game);
void mobs_move(game_s *game);
void mob_damage(game_s *game);
void mob_killed(game_s *game);

void end_game(game_s *game);

void draw_lvl_ext2(game_s *game);

void place_tower(game_s *game);
void tower_shooting(game_s *game);
void move_proj_to_mob(proj_t *proj, mob_t *mob, sfClock *c);
mob_t *identify_mob(game_s *game, void *adress);
void proj_damage(game_s *game);
void actualize_mob_stats(mob_t *mob, int lvl);

void sell_tower(game_s *game, tower_t *towers);
void upgrade_tower(game_s *game, tower_t *towers);

void slow_behaviour(game_s *game);
void dot_behaviour(game_s *game);

void animation_mobs(game_s *game);
void animation_towers(game_s *game);

void position_range_to_tower(tower_t *towers, game_s *game);

void events_tower_mouse(game_s *game, sfEvent event);

void draw_map_editor(game_s *game);

#endif
