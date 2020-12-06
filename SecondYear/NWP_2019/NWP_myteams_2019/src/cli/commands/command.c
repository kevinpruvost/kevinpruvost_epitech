/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

static const command_id_t commands[] = {\
{"help", &help_command}, \
{"login", &send_command}, \
{"logout", &send_command}, \
{"users", &send_command}, \
{"user", &send_command}, \
{"send", &send_command}, \
{"messages", &send_command}, \
{"subscribe", &send_command}, \
{"subscribed", &send_command}, \
{"unsubscribe", &send_command}, \
{"use", &send_command}, \
{"create", &send_command}, \
{"list", &send_command}, \
{"info", &send_command}, \
{"NULL", NULL}\
};

static int unknown_comm(void)
{
    printf("Unknown Command.\n");
    return UNKNOWN_COMMAND;
}

static int identify_command(char * line, account_t * account)
{
    char ** parameters = treat_arguments(line);
    int ret = EXIT_SUCCESS;

    for (int i = 0; commands[i].func != NULL; ++i) {
        if (strcmp(parameters[0], commands[i].title) == 0) {
            ret = commands[i].func(line, account);
            free_2darray((void **)parameters);
            return ret;
        }
    }
    free_2darray((void **)parameters);
    return unknown_comm();
}

int check_command(char * line, account_t * account)
{
    while (line[0] <= 32 || line[0] >= 127) {
        if (line[0] == 0)
            return UNKNOWN_COMMAND;
        ++line;
    }

    if (line[0] != '/')
        return unknown_comm();
    ++line;
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = 0;
    return identify_command(line, account);
}