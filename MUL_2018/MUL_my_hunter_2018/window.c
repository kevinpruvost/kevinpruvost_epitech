/*
** EPITECH PROJECT, 2018
** window.c
** File description:
** Function for the windows
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

sfText *scoretext_creation(sfText *score, int width, int height)
{
    sfVector2f position;
    sfFont *font = sfFont_createFromFile("fonts/duckhunt.ttf");

    position.x = (width / 10);
    position.y = (height / 8 * 7);
    score = sfText_create();
    sfText_setPosition(score, position);
    sfText_setString(score, "ah");
    sfText_setFont(score, font);
    sfText_setCharacterSize(score, width / 15);

    return (score);
}

int my_hunter(win_prop *w_prop, sounds *sounds_prop, game_info *game_infos)
{
    duck_prop duck = set_duck_props(duck, w_prop);
    cross_prop cr = set_cross_props(cr, w_prop, sounds_prop);
    back_prop back = set_background_props(back, w_prop);
    int end = 0;

    if (!w_prop->window)
        return EXIT_FAILURE;
    while (end == 0 && sfRenderWindow_isOpen(w_prop->window) == 1) {
        check_clean_window(w_prop, game_infos, &end);
        data_change(w_prop, &duck, &cr, game_infos);
        render_window(w_prop, back, duck, game_infos);
        sfRenderWindow_drawSprite(w_prop->window, cr.sprite, NULL);
        sfRenderWindow_display(w_prop->window);
    }
    end_my_duck(duck.sprite, w_prop, sounds_prop, game_infos);
}

int main_menu(win_prop *w_prop, sounds *sounds_prop, game_info *game_infos)
{
    main_menu_content m_cont;

    m_cont.background = set_background_main_menu(w_prop);
    m_cont.b1 = button1_creation(m_cont.b1, w_prop->width, w_prop->height);
    m_cont.b2 = button2_creation(m_cont.b2, w_prop->width, w_prop->height);
    m_cont.cursor = 1;
    music_launching(sounds_prop);
    sfRenderWindow_setMouseCursorVisible(w_prop->window, 0);
    if (!w_prop->window)
        return EXIT_FAILURE;
    sfRenderWindow_setFramerateLimit(w_prop->window, w_prop->fps);
    m_cont.cursor = main_menu_window(&m_cont, w_prop);
    if (m_cont.cursor == 2) {
        reset_game(game_infos);
        my_hunter(w_prop, sounds_prop, game_infos);
    } else {
        end_window(w_prop, sounds_prop);
        return (0);
    }
}

int set_vars(int wi, int he, float ips)
{
    win_prop w_prop;
    sounds sounds_prop;
    game_info game_infos;
    char *all_star = "sounds/All_Star.ogg";
    char *shooting = "sounds/shooting_snd.wav";

    w_prop = set_w_prop(w_prop, wi, he, ips);
    sounds_prop.music = sfMusic_createFromFile(all_star);
    sounds_prop.shot_buffer = sfSoundBuffer_createFromFile(shooting);
    sounds_prop.shot = sfSound_create();
    game_infos.AMMO = 3;
    game_infos.score = 0;
    sfSound_setBuffer(sounds_prop.shot, sounds_prop.shot_buffer);
    sfSound_setVolume(sounds_prop.shot, 10);
    main_menu(&w_prop, &sounds_prop, &game_infos);
}

int main(int ac, char **av)
{
    char *message = load_file_in_mem("help_msg");

    if (av[1] == "-h")
        my_putstr(message);
    if (ac == 1) {
        set_vars(800, 800, 30);
    } else if (ac == 4) {
        set_vars(my_atoi(av[1]), my_atoi(av[2]), my_getfloat(av[3]));
    } else
        my_putstr(message);
}
