/*
** EPITECH PROJECT, 2019
** iteration_error.c
** File description:
** iteration pour erreurs
*/

#include "my.h"

void iteration_error(mini_t *w)
{
    w->error = 0;
    for (; w->seps != NULL && w->seps->sep[0] != ';';) {
        iteration_launch_programs_for(w);
    }
}
