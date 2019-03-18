/*
** EPITECH PROJECT, 2018
** my_defender
** File description:
** my_defender
*/

#include "my.h"

void game_loop(void)
{
    game_s *game = create_game_s();
    funcs_game_t *main_funcs = create_main_funcs();

    if (!game)
        return;
    sfRenderWindow_setFramerateLimit(game->win, 60);
    sfRenderWindow_setMouseCursorVisible(game->win, sfFalse);
    while (sfRenderWindow_isOpen(game->win) == 1) {
        main_funcs->events[game->page](game);
        main_funcs->draws[game->page](game);
        if (sfMusic_getStatus(game->music) != sfPlaying)
            sfMusic_play(game->music);
    }
    destroy(game, main_funcs);
}

int my_resultint_random(char *buff)
{
    for (int i = 0; i < 10; i++) {
        if (buff[i] < '0' || buff[i] > '9' ||
            buff[i] != rand() % 9 + '0')
            buff[i] = rand() % 9 + '0';
    }
    return (my_atoi(buff));
}

void reset_random(void)
{
    int nb = 5;
    void *adress = &nb;
    long long long_seed = (long long)(adress);
    unsigned int res = long_seed;

    srand(res);
}

int main(int ac, char **av, char **env)
{
    char *msg = load_file_in_mem("assets/txt/help");

    reset_random();
    if (ac == 2 && is_str(av[1], "-h") == 1 && msg != NULL) {
        my_putstr(msg);
    } else if (is_env_display(env) == 1){
        game_loop();
    } else
        return (84);
    free(msg);
    return (0);
}
