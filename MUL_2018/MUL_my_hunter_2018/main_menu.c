/*
** EPITECH PROJECT, 2018
** main_menu.c
** File description:
** functions for main menu
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/my.h"

void cursor_managing(int *cursor)
{
    if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
        *cursor -= 1;
        timer(0.1);
    }
    if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
        *cursor += 1;
        timer(0.1);
    }
}

sfText *button1_creation(sfText *score, int width, int height)
{
    sfVector2f position;
    sfFont *font = sfFont_createFromFile("fonts/duckhunt.ttf");

    position.x = width / 6 * 3;
    position.y = height / 8 * 6;
    score = sfText_create();
    sfText_setPosition(score, position);
    sfText_setString(score, "QUITTER");
    sfText_setFont(score, font);
    sfText_setCharacterSize(score, width / 15);

    return (score);
}

sfText *button2_creation(sfText *score, int width, int height)
{
    sfVector2f position;
    sfFont *font = sfFont_createFromFile("fonts/duckhunt.ttf");

    position.x = width / 6 * 3;
    position.y = height / 8 * 5;
    score = sfText_create();
    sfText_setPosition(score, position);
    sfText_setString(score, "JOUER");
    sfText_setFont(score, font);
    sfText_setCharacterSize(score, width / 15);

    return (score);
}

void manage_button_1(sfText **button, int *cursor, sfRenderWindow *window)
{
    if (*cursor > 2)
        *cursor	= 1;
    if (*cursor < 1)
        *cursor = 2;
    if (*cursor == 1)
        sfText_setColor(*button, sfRed);
    else
        sfText_setColor(*button, sfWhite);
    sfRenderWindow_drawText(window, *button, NULL);
}

void manage_button_2(sfText **button, int *cursor, sfRenderWindow *window)
{
    if (*cursor == 2)
        sfText_setColor(*button, sfRed);
    else
        sfText_setColor(*button, sfWhite);
    sfRenderWindow_drawText(window, *button, NULL);
}
