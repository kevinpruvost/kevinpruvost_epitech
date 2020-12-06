/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_create_utils
*/

#include "server.h"

int add_reply_helper(client_t *cli, gthread_t *thread, reply_t *new_reply,
    global_t *glob)
{
    char *event = NULL;

    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s : %s : %s : "\
            "%s : %s : %s",
            EVENT_THREAD_MSG_RECEIVED, cli->team->base.name,
            thread->base.name, cli->base.name, cli->team->base.uuid,
            thread->base.uuid, cli->base.uuid, new_reply->message) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s : %s : %s : %s : %s",
            EVENT_THREAD_MSG_RECEIVED, cli->team->base.name,
            thread->base.name, cli->base.name, cli->team->base.uuid,
            thread->base.uuid, cli->base.uuid, new_reply->message);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}