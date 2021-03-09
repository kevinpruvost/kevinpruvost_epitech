/*
** EPITECH PROJECT, 2019
** actions_and_events.c
** File description:
** actions_and_events.c
*/

#include "bonus.h"

int actions_and_events_animation(window_t *b, ai_t *w)
{
    get_time(b->bgd->time_anim, b->clock);
    if (b->bgd->time_anim->seconds < 0.48 / 12)
        return (0);
    anim_sprite(b->bgd, 0, 1);
    reset_time(b->bgd->time_anim, b->clock);
    return (0);
}

char *create_string_t(char *to_copy, int size)
{
    char *copied;

    copied = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i != size; i++)
        copied[i] = 0;
    for (int i = 0; to_copy[i] != 0; i++)
        copied[i] = to_copy[i];
    copied[size] = 0;
    return (copied);
}

int actions_and_events_text(window_t *b, ai_t *w)
{
    char *t_speed = create_string_t("Vitesse :      \0", 50);
    char *t_rotation = create_string_t("Rotation :   \0", 50);
    char *d_speed = create_string(10);
    char *d_rotation = create_string(10);

    if (w->f_speed != 0)
        sprintf(d_speed, "%.2f", w->f_speed);
    else
        sprintf(d_speed, "-%.2f", w->b_speed);
    sprintf(d_rotation, "%.2f", w->wheels_dir * -1);
    strcat(t_speed, d_speed);
    strcat(t_rotation, d_rotation);
    edit_text_str(b->speed, t_speed);
    edit_text_str(b->rotation, t_rotation);
    free(t_speed);
    free(t_rotation);
    free(d_speed);
    free(d_rotation);
}

int actions_and_events(window_t *b, ai_t *w)
{
    actions_and_events_animation(b, w);
    actions_and_events_text(b, w);
    get_time(b->stop->time_anim, b->clock);
    if (b->stop->time_anim->seconds <= 0.02)
        return (0);
    actions_and_events_keys(b, w);
}
