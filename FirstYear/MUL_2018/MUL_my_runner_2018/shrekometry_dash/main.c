/*
** EPITECH PROJECT, 2018
** shrekometry_dash.c
** File description:
** game functions
*/

#include "my.h"

void death_animation(gm_vars *gm, w_prop *win)
{
    float seconds = clock_getseconds(gm->player->clock_anim);

    (gm->alive == 0 && gm->pause < 3) ? (gm->pause = 2) : (0);
    if (gm->pause == 2) {
        sfSound_play(gm->player->death_sound->sound);
        sfClock_restart(gm->player->clock_anim);
        gm->player->rect.left = 0;
        gm->player->rect.top = 105;
        gm->pause = 3;
    }
    if (gm->pause == 3) {
        if (seconds >= 0.4) {
            gm->player->rect.left += 43;
            if (gm->player->rect.left > 208)
                gm->pause = 4;
            else
                sfSprite_setTextureRect(gm->player->sprite, gm->player->rect);
            sfClock_restart(gm->player->clock_anim);
        }
    }
}

gm_vars *init_game(gm_vars *gm, w_prop *win)
{
    y_sol_management(gm, win);
    gm->player->pos.y = gm->player->y_sol - 1;
    gm->alive = 1;
    return (gm);
}

void *window_game(gm_vars **gm, w_prop **win)
{
    while (sfRenderWindow_pollEvent((*win)->win, &(*win)->event)) {
        if ((*win)->event.type == sfEvtClosed)
            sfRenderWindow_close((*win)->win);
        if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
            (*gm)->stop = 1;
    }
}

gm_vars *process_game(gm_vars *gm, w_prop *win)
{
    scene_movement(gm, win);
    gravity(gm, win);
    jump_management(gm, win);
    sfRenderWindow_drawSprite(win->win, gm->back0->sprite, NULL);
    sfRenderWindow_drawSprite(win->win, gm->back1->sprite, NULL);
    sfRenderWindow_drawSprite(win->win, gm->back2->sprite, NULL);
    draw_blocks(gm, win);
    cursor_point(gm, win);
    y_sol_management(gm, win);
    death_animation(gm, win);
    sfRenderWindow_drawSprite(win->win, gm->player->sprite, NULL);
    if (gm->pause == 1)
        sfRenderWindow_drawSprite(win->win, gm->pause_txt->sprite, NULL);
    sfRenderWindow_display(win->win);
    analyse_end(gm, win);
    return (gm);
}

int game(char **map, w_prop *win)
{
    gm_vars *gm = create_gm_vars(win, map);

    gm = init_game(gm, win);
    while (gm->stop == 0 && sfRenderWindow_isOpen(win->win) == 1) {
        window_game(&gm, &win);
        sfRenderWindow_clear(win->win, sfTransparent);
        clear_framebuffer(win->width, win->height, win->fb);
        gm = process_game(gm, win);
    }
    if (gm->stop == 1) {
        destroy_game(gm);
        main_menu(map, win);
    } else {
        destroy_game(gm);
        destroy_win_prop(win);
    }
    return (0);
}

