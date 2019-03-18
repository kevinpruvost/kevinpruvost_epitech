/*
** EPITECH PROJECT, 2019
** score.c
** File description:
** score funcs
*/

#include "my.h"

void get_score(int scores[3])
{
    int fd = -1;
    char *buffer;

    fd = open("assets/txt/score", O_RDWR);
    for (int i = 0; i < 3; i++)
        scores[i] = 0;
    if (fd != -1) {
        for (int i = 0; i < 3; i++) {
            buffer = get_next_line(fd);
            scores[i] = my_atoi(buffer);
            free(buffer);
        }
        close(fd);
    }
}

char *scores_to_str(int scores[3])
{
    char *n1 = str_add(my_getnbr(scores[0]), "\n");
    char *n2 = str_add(my_getnbr(scores[1]), "\n");
    char *n3 = my_getnbr(scores[2]);
    char *n_final = str_add(str_add(n1, n2), n3);

    free(n1);
    free(n2);
    free(n3);
    return (n_final);
}

void write_score(int scores[3])
{
    int fd = -1;
    char *to_write = scores_to_str(scores);

    fd = open("assets/txt/score", O_RDWR);
    if (fd != -1) {
        write(fd, to_write, my_strlen(to_write));
    }
    free(to_write);
}

void actualize_score(game_s *game)
{
    sfText_setString(game->mm_vars->ranks[0]->text, my_getnbr(game->scores[0]));
    sfText_setString(game->mm_vars->ranks[1]->text, my_getnbr(game->scores[1]));
    sfText_setString(game->mm_vars->ranks[2]->text, my_getnbr(game->scores[2]));
    game->mm_vars->ranks[0]->content = my_getnbr(game->scores[0]);
    game->mm_vars->ranks[1]->content = my_getnbr(game->scores[1]);
    game->mm_vars->ranks[2]->content = my_getnbr(game->scores[2]);
}

void add_new_score(game_s *game)
{
    int score = game->score;
    int place = 3;

    for (int i = 2; i >= 0; i--)
        if (score > game->scores[i])
            place = i;
    if (place == 1 || place == 2 || place == 0)
        game->scores[place] = score;
}
