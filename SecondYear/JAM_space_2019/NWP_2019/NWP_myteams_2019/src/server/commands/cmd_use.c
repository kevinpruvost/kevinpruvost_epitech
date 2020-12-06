/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_use(client_t *cli, header_t *header, global_t *glob)
{
    use_t *use = (use_t *)header;
    team_t *team = NULL;
    channel_t *channel = NULL;
    gthread_t *thread = NULL;

    if (use->nb_uuid_defined < 1) {
        cli->team = NULL;
        cli->channel = NULL;
        cli->thread = NULL;
        dprintf(cli->fd, "%d You are at the domain's root\r\n", NO_EVENT);
        return (EXIT_SUCCESS);
    }
    team = bvector_get_from_uuid(glob->teams, use->uuids[0]);
    if (!team) {
        if (cli->team && cli->channel) {
            thread = bvector_get_from_uuid(cli->channel->threads, use->uuids[0]);
            if (!thread)
                dprintf(cli->fd, "%d Thread does not exist\r\n", EVENT_ERROR_UNKNOWN_THREAD);
            else {
                cli->thread = thread;
                dprintf(cli->fd, "%d Using: %s -> %s -> %s\r\n", NO_EVENT, cli->team->base.name, cli->channel->base.name, thread->base.name);
            }
            return (EXIT_SUCCESS);
        }
        if (cli->team) {
            channel = bvector_get_from_uuid(cli->team->channels, use->uuids[0]);
            if (!channel)
                dprintf(cli->fd, "%d Channel does not exist\r\n", EVENT_ERROR_UNKNOWN_CHANNEL);
            else {
                cli->channel = channel;
                dprintf(cli->fd, "%d Using: %s -> %s -> NULL\r\n", NO_EVENT, cli->team->base.name, channel->base.name);
            }
            return (EXIT_SUCCESS);
        }
        dprintf(cli->fd, "%d Team does not exist\r\n", EVENT_ERROR_UNKNOWN_TEAM);
        return (EXIT_FAILURE);
    }
    cli->team = team;
    if (use->nb_uuid_defined < 2) {
        cli->channel = NULL;
        cli->thread = NULL;
        dprintf(cli->fd, "%d Using: %s -> NULL -> NULL\r\n", NO_EVENT, team->base.name);
        return (EXIT_SUCCESS);
    }
    channel = bvector_get_from_uuid(team->channels, use->uuids[1]);
    if (!channel) {
        dprintf(cli->fd, "%d Channel does not exist\r\n", EVENT_ERROR_UNKNOWN_CHANNEL);
        cli->team = NULL;
        return (EXIT_FAILURE);
    }
    cli->channel = channel;
    if (use->nb_uuid_defined < 3) {
        cli->thread = NULL;
        dprintf(cli->fd, "%d Using: %s -> %s -> NULL\r\n", NO_EVENT, team->base.name, channel->base.name);
        return (EXIT_SUCCESS);
    }
    thread = bvector_get_from_uuid(channel->threads, use->uuids[2]);
    if (!thread) {
        dprintf(cli->fd, "%d Thread does not exist\r\n", EVENT_ERROR_UNKNOWN_THREAD);
        cli->team = NULL;
        cli->channel = NULL;
        return (EXIT_FAILURE);
    }
    cli->thread = thread;
    dprintf(cli->fd, "%d Using: %s -> %s -> %s\r\n", NO_EVENT, team->base.name, channel->base.name, thread->base.name);
    return (EXIT_SUCCESS);
}