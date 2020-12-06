/*
** EPITECH PROJECT, 2018
** text_obj.c
** File description:
** text func
*/

#include "my.h"

text_obj *create_text_obj(char *txt, sfVector2f sc, sfVector2f pos, sfColor c)
{
    text_obj *text = malloc(sizeof(text_obj));

    text->content = txt;
    text->font = sfFont_createFromFile("assets/fonts/font2.ttf");
    text->text = sfText_create();
    text->scale = sc;
    sfText_setCharacterSize(text->text, 36);
    sfText_setScale(text->text, sc);
    text->chsize = 36;
    sfText_setColor(text->text, c);
    sfText_setFont(text->text, text->font);
    text->pos = pos;
    sfText_setPosition(text->text, text->pos);
    sfText_setString(text->text, txt);
    return (text);
}

void destroy_text_obj(text_obj *text)
{
    sfFont_destroy(text->font);
    sfText_destroy(text->text);
    free(text);
}
