/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_info(client_t *cli, header_t *header, global_t *glob)
{
    if (cli->thread) {
        dprintf(cli->fd, "%d %s : %s : %s : %s\r\n", NO_EVENT,
            cli->thread->base.uuid, cli->thread->base.name,
            cli->thread->timestamp, cli->thread->message);
        return (EXIT_SUCCESS);
    }
    if (cli->channel) {
        dprintf(cli->fd, "%d %s : %s : %s\r\n", NO_EVENT,
            cli->channel->base.uuid, cli->channel->base.name,
            cli->channel->description);
        return (EXIT_SUCCESS);
    }
    if (cli->team) {
        dprintf(cli->fd, "%d %s : %s : %s\r\n", NO_EVENT,
            cli->team->base.uuid, cli->team->base.name,
            cli->team->description);
        return (EXIT_SUCCESS);
    }
    dprintf(cli->fd, "%d %s : %s : %d\r\n", EVENT_PRINT_USERS,
        cli->base.uuid, cli->base.name, cli->is_connected);
    return (EXIT_SUCCESS);
}