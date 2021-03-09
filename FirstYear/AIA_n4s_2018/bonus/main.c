/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main bonus
*/

#include "bonus.h"

int main(int ac, char **av)
{
    size_t buffer = 255;
    char *line = NULL;
    ai_t *w = create_ai_t();
    window_t *b;

    if (help_option(av, ac) == 1)
        return (1);
    if (w == NULL)
        return (84);
    b = create_window_t(w);
    if (b == NULL)
        return (84);
    my_putstr("start_simulation\n");
    for (int err = 0, i = 1; err == 0
    && sfRenderWindow_isOpen(b->win); i++) {
        (i == 1) ? (err = get_info_lidar(w)) : (0);
        err = render_game(b, w);
    }
    destroy_ai_t(w);
    destroy_window_t(b);
    return (0);
}
