/*
** EPITECH PROJECT, 2018
** window_complements.c
** File description:
** complete window.c functions
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void reset_game(game_info *game_infos)
{
    game_infos->AMMO = 3;
    game_infos->score = 0;
}

void end_window(win_prop *w_prop, sounds *sounds_prop)
{
    sfRenderWindow_close(w_prop->window);
    sfSound_stop(sounds_prop->shot);
    sfSound_destroy(sounds_prop->shot);
    sfSoundBuffer_destroy(sounds_prop->shot_buffer);
    sfMusic_stop(sounds_prop->music);
    sfMusic_destroy(sounds_prop->music);
    sfRenderWindow_destroy(w_prop->window);
}

int main_menu_window(main_menu_content *mm_content, win_prop *w_prop)
{
    int stop = 0;

    while (stop == 0) {
        if (sfKeyboard_isKeyPressed(sfKeySpace) != sfFalse)
            stop = 1;
        if (sfRenderWindow_isOpen(w_prop->window) != 1)
            stop = 1;
        sfRenderWindow_clear(w_prop->window, sfTransparent);
        sfRenderWindow_drawSprite(w_prop->window, mm_content->background, NULL);
        cursor_managing(&mm_content->cursor);
        manage_button_1(&mm_content->b1, &mm_content->cursor, w_prop->window);
        manage_button_2(&mm_content->b2, &mm_content->cursor, w_prop->window);
        sfRenderWindow_display(w_prop->window);
    }
    return (mm_content->cursor);
}

void end_my_duck(sfSprite *sp, win_prop *w_p, sounds *snd_p, game_info *gm_inf)
{
    sfSprite_destroy(sp);
    main_menu(w_p, snd_p, gm_inf);
}
