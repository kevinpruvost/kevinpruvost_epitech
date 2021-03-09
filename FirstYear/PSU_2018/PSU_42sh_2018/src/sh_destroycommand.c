/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Destroy a command instance.
*/

#include <stdlib.h>
#include <string.h>

#include "fortytwosh.h"

void sh_destroycommand(command_t *command)
{
    free((void *) command->input);
    free(command->argv);
    free(command);
}
