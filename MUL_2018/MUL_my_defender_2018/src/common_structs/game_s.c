/*
** EPITECH PROJECT, 2019
** create_game_s.c
** File description:
** game_s funcs
*/

#include "my.h"
#include "struct.h"
#include "libs.h"

void create_sound_fx(game_s *game)
{
    game->sound_fx[DEATH] = sfMusic_createFromFile("assets/sounds/death1.ogg");
    game->sound_fx[DRAGON] = sfMusic_createFromFile
    ("assets/sounds/dragon_sound.ogg");
    game->sound_fx[SFD] = sfMusic_createFromFile("assets/sounds/sfd_sound.ogg");
    game->sound_fx[NWAVE] = sfMusic_createFromFile("assets/sounds/what.ogg");
    game->sound_fx[DEATH1] = sfMusic_createFromFile
        ("assets/sounds/death_k.ogg");
    game->sound_fx[DEATH2] = sfMusic_createFromFile("assets/sounds/death2.ogg");
    game->music = sfMusic_createFromFile("assets/sounds/all_star.ogg");
    sfMusic_setVolume(game->music, 50);
    game->beep = sfMusic_createFromFile("assets/sounds/beep_button.ogg");
}

void create_range_preview(game_s *game)
{
    sfIntRect rect = {0, 0, 200, 200};
    sfVector2f pos = {0, 0};

    game->range[0] = create_game_obj
    ("assets/sprites/range.png", rect, pos, game->clock);
    game->range[1] = create_game_obj
    ("assets/sprites/range.png", rect, pos, game->clock);
    mod_scale(game->range[1]->sprite, 1.75);
    mod_scale(game->range[0]->sprite, 1.22);
    center_game_object(game->range[0]);
    center_game_object(game->range[1]);
    pos.x = 500;
    pos.y = 500;
    game->start_button = create_game_obj
        ("assets/sprites/start_button.png", rect, pos, game->clock);
    mod_scale(game->start_button->sprite, 1);
    game->start = 0;
    center_game_object(game->start_button);
}

game_s *create_game_s(void)
{
    game_s *game = malloc(sizeof(game_s));
    sfVideoMode mode = {1000, 1000, 32};
    char *name = "Shrek Tower Defense";

    game->win = sfRenderWindow_create(mode, name, sfResize | sfClose, NULL);
    game->page = MAINMENU;
    game->old_page = MAINMENU;
    game->clock = sfClock_create();
    game->mm_vars = create_menu_s(game->clock);
    game->lvl_vars = create_lvl_s(game->clock);
    game->htp_vars = create_htp_s(game->clock);
    game->sett_vars = create_settings_s(game->clock);
    game->maped_vars = create_map_editor_s(game->clock);
    game->map = create_map(game->clock);
    game->score = 0;
    create_sound_fx(game);
    create_range_preview(game);
    get_score(game->scores);
    return (game);
}

void destroy_game_s(game_s *game)
{
    sfRenderWindow_destroy(game->win);
    sfClock_destroy(game->clock);
    sfMusic_stop(game->music);
    sfMusic_destroy(game->music);
    sfMusic_destroy(game->beep);
    for (int i = 0; i < 6; i++)
        sfMusic_destroy(game->sound_fx[i]);
    destroy_menu_s(game->mm_vars);
    destroy_lvl_s(game->lvl_vars);
    destroy_htp_s(game->htp_vars);
    destroy_map_editor_s(game->maped_vars);
    destroy_settings_s(game->sett_vars);
    destroy_map(game->map);
    destroy_game_obj(game->range[0]);
    destroy_game_obj(game->range[1]);
    destroy_game_obj(game->start_button);
    write_score(game->scores);
    free(game);
}
