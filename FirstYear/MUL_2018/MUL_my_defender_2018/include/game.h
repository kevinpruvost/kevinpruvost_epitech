/*
** EPITECH PROJECT, 2019
** game.h
** File description:
** structs for game
*/

#ifndef GAME_H
#define GAME_H

typedef enum tower_type {
    DMG,
    DOT,
    SLOW,
    HEAVY
} tower_type;

typedef enum mob_type {
    TANK,
    NORM,
    SPD,
    BUFF
} mob_type;
/*
typedef enum proj_type {
    DMG,
    DOT,
    SLOW,
    HEAVY
} proj_type;
*/
typedef struct lib_types_t {
    sfTexture *texture_tower[4];
    sfTexture *texture_mob[4];
    sfTexture *texture_proj[4];
    float damage_tower[4];
    float range_tower[4];
    float atk_speed_tower[4];
    float price_tower[4];
    float speed_mob[4];
    float hp_mob[4];
} lib_types_t;
void lib_types_textures(lib_types_t *lib_types);
lib_types_t *create_lib_types(void);
void destroy_lib_types(lib_types_t *lib_types);

typedef struct tower_t {
    game_obj *props;
    int type;
    int lvl;
    float damage;
    float range;
    float atk_speed;
    time_obj *atk_speed_time;
    int firing;
    struct tower_t *next;
} tower_t;

typedef struct proj_t {
    game_obj *props;
    int type;
    float damage;
    float speed;
    void *target;
    int arrived;
    struct proj_t *next;
} proj_t;

typedef struct mob_t {
    game_obj *props;
    int type;
    int lvl;
    float speed;
    float hp;
    int path_pos;
    int arrived;
    game_obj *health_bar;
    int slow;
    int dot;
    time_obj *time_slow;
    time_obj *time_dot;
    struct mob_t *next;
} mob_t;

typedef struct player_t {
    int money;
    text_obj *money_txt;
    int hp;
    text_obj *hp_txt;
    int wave;
    text_obj *wave_txt;
    int nb_mobs_to_spawn;
    time_obj *time_played;
    time_obj *time_wave;
    time_obj *time_spawn;
    game_obj *tower_spectres[4];
    game_obj *tower_buttons[4];
    game_obj *upgrade_button;
    game_obj *sell_button;
    game_obj *tower_descs[4];
} player_t;
player_t *create_player(sfClock *clock);
void destroy_player(player_t *player);
void create_spectres_player(player_t *player, sfClock *clock);
game_obj *create_upgrade_button(sfClock *);
game_obj *create_sell_button(sfClock *);

typedef struct order_t {
    int x;
    int y;
    int order;
} order_t;

typedef struct sim_map_t {
    int x_test;
    int y_test;
    int **map_id_test;
    int sens_x;
    int sens_y;
    int n;
    int x;
    int y;
    int done;
    int order;
} sim_map_t;

typedef struct map_t {
    int map_id[10+1][6+1];
    game_obj *map_case[10+1][6+1];
    void (*change_case[7])(game_obj *);
    order_t **orders;
} map_t;
map_t *create_map(sfClock *clock);
void destroy_map(map_t *map);
void change_map_1(game_obj *map_case);
void change_map_2(game_obj *map_case);
void change_map_3(game_obj *map_case);
void change_map_4(game_obj *map_case);
void change_map_5(game_obj *map_case);
void change_map_6(game_obj *map_case);
void change_map_empty(game_obj *map_case);
void generate_random_map(map_t *map);
int stuck(int **map_id, int x, int y);
void print_map(map_t *map);
void regenerate_random_map(map_t *map);
void clear_map(map_t *map);
void map_spriting(map_t *map);
int possible_way(map_t *map, int x, int y);
int **map_id_replace(int **map_id);

typedef struct level_s {
    bgd_obj *background;
    bgd_obj *grid;
    game_obj *cursor;
    sfMusic *music;
    int pause;
    game_obj *pause_objs[3];
    text_obj *tower_infos[5];
    text_obj *no_tower_info;
    lib_types_t *lib_types;
    tower_t *towers;
    proj_t *projs;
    mob_t *mobs;
    player_t *player;
    void *adress;
    game_obj *next_wave;
    int next_waving;
} lvl_s;
lvl_s *create_lvl_s(sfClock *);
void destroy_lvl_s(lvl_s *);
text_obj *create_tower_infos(text_obj *tower_infos[5], text_obj *);

#endif
