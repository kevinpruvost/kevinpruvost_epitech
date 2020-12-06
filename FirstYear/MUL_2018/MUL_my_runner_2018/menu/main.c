/*
** EPITECH PROJECT, 2018
** main_menu.c
** File description:
** main_menu functions
*/

#include "my.h"

int cursor_id_value(int cursor_id)
{
    if (sfKeyboard_isKeyPressed(sfKeyDown) == 1)
        cursor_id++;
    if (sfKeyboard_isKeyPressed(sfKeyUp) == 1)
        cursor_id--;
    if (cursor_id > 1)
        cursor_id = 0;
    if (cursor_id < 0)
        cursor_id = 1;
    return (cursor_id);
}

int cursor_managing(int cursor_id, game_obj *cursor)
{
    sfTime time = sfClock_getElapsedTime(cursor->clock);
    float seconds = time.microseconds / 1000000.0;
    sfVector2f scale = cursor->scale;
    sfVector2f pos0 = {180 * scale.x, 340 * scale.y};
    sfVector2f pos1 = {180 * scale.x, 440 * scale.y};

    if (seconds <= 0.2)
        return (cursor_id);
    if (sfKeyboard_isKeyPressed(sfKeyUp) == 1 ||
        sfKeyboard_isKeyPressed(sfKeyDown) == 1)
        sfClock_restart(cursor->clock);
    cursor_id = cursor_id_value(cursor_id);
    if (cursor_id == 1)
        sfSprite_setPosition(cursor->sprite, pos1);
    if (cursor_id == 0)
        sfSprite_setPosition(cursor->sprite, pos0);
    return (cursor_id);
}

bgd_obj *animation(bgd_obj *gif)
{
    sfTime time = sfClock_getElapsedTime(gif->clock);
    float seconds = time.microseconds / 1000000.0;

    if (seconds > 1.0 / 14.5) {
        sfClock_restart(gif->clock);
        gif->rect.left += 800;
        if (gif->rect.left <= 10400)
            sfSprite_setTextureRect(gif->sprite, gif->rect);
    }
    return (gif);
}

void anim_before_play(w_prop *win)
{
    int stop = 0;
    bgd_obj *gif = create_image(win);
    sfMusic *music = sfMusic_createFromFile("sounds/kicking_sound.ogg");

    sfMusic_setVolume(music, 14);
    sfMusic_play(music);
    while (stop == 0 && sfRenderWindow_isOpen(win->win) == 1) {
        while (sfRenderWindow_pollEvent(win->win, &win->event))
            if (win->event.type == sfEvtClosed)
                sfRenderWindow_close(win->win);
        sfRenderWindow_clear(win->win, sfTransparent);
        clear_framebuffer(win->width, win->height, win->fb);
        sfRenderWindow_drawSprite(win->win, gif->sprite, NULL);
        sfRenderWindow_display(win->win);
        gif = animation(gif);
        if (gif->rect.left > 11200)
            stop = 1;
    }
    sfMusic_destroy(music);
    destroy_bgd_obj(gif);
}

int main_menu(char **map, w_prop *win)
{
    mm_vars *mm = create_mm_vars(win);

    while (mm->stop == 0 && sfRenderWindow_isOpen(win->win) == 1) {
        clear_main_menu(win, &mm->stop);
        if (sfMusic_getStatus(win->music) != sfPlaying)
            sfMusic_play(win->music);
        mm->cursor_id = cursor_managing(mm->cursor_id, mm->cursor);
        draw_main_menu(win, mm);
        sfRenderWindow_display(win->win);
    }
    if (mm->cursor_id == 1) {
        destroy_mm_vars_without_music(mm);
        destroy_win_prop(win);
    } else {
        anim_before_play(win);
        destroy_mm_vars_without_music(mm);
        game(map, win);
    }
}
