/*
** EPITECH PROJECT, 2018
** main_menu_processes.c
** File description:
** main_menu func
*/

#include "my.h"

void draw_main_menu(w_prop *win, mm_vars *mm)
{
    sfRenderWindow_drawSprite(win->win, mm->back->sprite, NULL);
    sfRenderWindow_drawText(win->win, mm->button1->text, NULL);
    sfRenderWindow_drawText(win->win, mm->button2->text, NULL);
    sfRenderWindow_drawSprite(win->win, mm->cursor->sprite, NULL);
}

mm_vars *create_mm_vars(w_prop *win)
{
    mm_vars *mm = malloc(sizeof(mm_vars));

    mm->stop = 0;
    mm->cursor_id = 0;
    mm->back = back_create(win->scale);
    mm->cursor = cursor_create(win->scale);
    mm->button1 = button1_create(win->scale);
    mm->button2 = button2_create(win->scale);
    return (mm);
}

mm_vars *destroy_mm_vars_with_music(mm_vars *mm)
{
    destroy_text_obj(mm->button1);
    destroy_text_obj(mm->button2);
    destroy_bgd_obj(mm->back);
    destroy_game_obj(mm->cursor);
    sfMusic_stop(mm->music);
    sfMusic_destroy(mm->music);
}

mm_vars	*destroy_mm_vars_without_music(mm_vars *mm)
{
    destroy_text_obj(mm->button1);
    destroy_text_obj(mm->button2);
    destroy_bgd_obj(mm->back);
    destroy_game_obj(mm->cursor);
}

void clear_main_menu(w_prop *win, int *stop)
{
    while (sfRenderWindow_pollEvent(win->win, &win->event)) {
        if (sfKeyboard_isKeyPressed(sfKeySpace) != sfFalse)
            *stop = 1;
        if (win->event.type == sfEvtClosed)
            sfRenderWindow_close(win->win);
    }
    sfRenderWindow_clear(win->win, sfTransparent);
    clear_framebuffer(win->width, win->height, win->fb);
}

