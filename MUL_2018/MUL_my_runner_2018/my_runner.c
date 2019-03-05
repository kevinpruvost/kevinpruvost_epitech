/*
** EPITECH PROJECT, 2018
** my_runner.c
** File description:
** my_runner main functions
*/

#include "include/my.h"

char **map_convert(char *map, int nb_col, int nb_rows)
{
    char **map_array;

    for (int i = 0, j = 0; map[i] != 0; i++, j++)
        if (map[i] == '\n') {
            (nb_col < j) ? (nb_col = j) : (0);
            j = 0, nb_rows++;
        }
    nb_col += 22;
    map_array = malloc(sizeof(char *) * (nb_rows + 1));
    for (int i = 0, k = 0; i < nb_rows; i++) {
        map_array[i] = malloc(sizeof(char) * (nb_col + 1));
        for (int j = 0; map[k] != '\n' && map[k] != 0; j++, k++)
            map_array[i][j] = map[k];
        for (int j = k; j < nb_col; j++)
            map_array[i][j] = ' ';
        k++, map_array[i][nb_col] = 0;
    }
    map_array[nb_rows] = NULL;
    return (map_array);
}

int my_runner(char *map, char **av)
{
    w_prop *window;
    char **map_array;
    int width = 800;
    int height = 800;
    float fps = 30.0;

    if (map == NULL)
        return (0);
    else
        map_array = map_convert(map, 0, 1);
    if (av[2] != NULL)
        fps = my_getfloat(av[2]);
    window = create_win_prop(width, height, fps);
    sfRenderWindow_setVerticalSyncEnabled(window->win, sfTrue);
    sfRenderWindow_setFramerateLimit(window->win, window->fps);
    sfRenderWindow_setMouseCursorVisible(window->win, sfFalse);
    main_menu(map_array, window);
}
