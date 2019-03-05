/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main for bonus
*/

#include "my.h"
#include "bonus.h"

void display_begin(char **env)
{
    char *ah;
    char *name = search_name(env);
    char *computer = search_computer(env);
    char *dir = malloc(sizeof(char) * 255);

    free(dir);
    dir = malloc(sizeof(char) * 255);
    getcwd(dir, 255);
    dir = format_dir(dir);
    my_putstr("[");
    my_putstr(name);
    my_putstr("@");
    my_putstr(computer);
    my_putstr(" ");
    my_putstr(dir);
    my_putstr("]$ ");
}

char *env_value(char *env)
{
    char *to_return = malloc(sizeof(char) * my_strlen(env));
    int i = 0;

    for (; env[i] != '=' && env[i] != 0; i++);
    (env[i] == '=') ? (i++) : (0);
    for (int j = 0; env[i] != 0; i++, j++)
        to_return[j] = env[i];
    return (to_return);
}

char *format_line(char *ah)
{
    while (ah[0] <= 32 && ah[0] > 0) {
        ah++;
    }
    return (ah);
}

int main(int ac, char **av, char **env)
{
    char *ah = malloc(sizeof(char) * 255);
    size_t bufsize = 255;
    size_t characters;
    int n = 0;

    while (1) {
        display_begin(env);
        getline(&ah, &bufsize, stdin);
        for (n = 0; ah[n] != '\n' && ah[n] != 0; n++);
        (ah[0] == 0 || ah[0] == 1) ? (ah = NULL) : (0);
        if (ah != NULL) {
            if (ah[n] == '\n')
                ah[n] = 0;
            ah = format_line(ah);
        }
        env = my_exec(2, ah, env);
        for (; n >= 0; n--) {
            ah[n] = 0;
        }
    }
}
