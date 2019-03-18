/*
** EPITECH PROJECT, 2019
** main_funcs.c
** File description:
** create main funcs struct
*/

#include "my.h"

funcs_game_t *create_main_funcs(void)
{
    funcs_game_t *main_funcs = malloc(sizeof(funcs_game_t));

    main_funcs->draws[MAINMENU] = draw_main_menu;
    main_funcs->events[MAINMENU] = event_main_menu;
    main_funcs->draws[LEVEL] = draw_lvl;
    main_funcs->events[LEVEL] = event_lvl;
    main_funcs->draws[HTP] = draw_htp;
    main_funcs->events[HTP] = event_htp;
    main_funcs->draws[SETTINGS] = draw_settings;
    main_funcs->events[SETTINGS] = event_settings;
    main_funcs->draws[MAP_EDITOR] = draw_map_editor;
    main_funcs->events[MAP_EDITOR] = event_map_editor;
    return (main_funcs);
}
