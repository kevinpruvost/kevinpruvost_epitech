/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main ai
*/

#include "my.h"

int main(int ac, char **av)
{
    size_t buffer = 255;
    char *line = NULL;
    ai_t *w = create_ai_t();

    help_option(av, ac);
    if (w == NULL)
        return (84);
    my_putstr("start_simulation\n");
    for (int err = 0, i = 1; err == 0; i++) {
        err = get_info_lidar(w);
        if (err == 0 && w->launch == 1)
            err = ai(w);
    }
    destroy_ai_t(w);
    return (0);
}
