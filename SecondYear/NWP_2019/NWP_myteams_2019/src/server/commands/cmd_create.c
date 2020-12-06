/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

static int add_team(create_t *create, client_t *cli, global_t *glob)
{
    team_t *new_team = create_team(create->name, create->body,
                                        cli->base.uuid, false);
    char *event = NULL;

    server_event_team_created(new_team->base.uuid, new_team->base.name,
                                                new_team->uuid_creator);
    if (!glob->teams)
        glob->teams = bvector_create(new_team, TEAM);
    else
        bvector_push_back(glob->teams, new_team, TEAM);
    if (!(event = malloc(snprintf(NULL, 0, "%d %s : %s : %s",
        EVENT_PRINT_TEAMS, new_team->base.uuid, new_team->base.name,
        new_team->description) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d %s : %s : %s", EVENT_PRINT_TEAMS, new_team->base.uuid,
                                new_team->base.name, new_team->description);
    send_event_to_clients(event, glob, NULL);
    return (EXIT_SUCCESS);
}

static int add_channel(create_t *create, team_t *team,
                            client_t *cli, global_t *glob)
{
    channel_t *new_channel = create_channel(create->name, create->body);
    char *event = NULL;

    server_event_channel_created(team->base.uuid, new_channel->base.uuid,
                                        new_channel->base.name);
    if (!team->channels)
        team->channels = bvector_create(new_channel, CHANNEL);
    else
        bvector_push_back(team->channels, new_channel, CHANNEL);
    if (!(event = malloc(snprintf(NULL, 0, "%d Channel sucessfully created !"\
        " %s %s %s\r\n", NO_EVENT, new_channel->base.uuid,
        new_channel->base.name, new_channel->description) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d Channel sucessfully created ! %s %s %s\r\n", NO_EVENT,
    new_channel->base.uuid, new_channel->base.name, new_channel->description);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}

static int add_thread(create_t *create, channel_t *channel,
                                client_t *cli, global_t *glob)
{
    gthread_t *new_thread = create_thread(create->name, create->body,
                                                    cli->base.uuid);
    char *event = NULL;

    server_event_thread_created(channel->base.uuid, new_thread->base.uuid,
                            new_thread->uuid_creator, new_thread->message);
    if (!channel->threads)
        channel->threads = bvector_create(new_thread, THREAD);
    else
        bvector_push_back(channel->threads, new_thread, THREAD);
    if (!(event = malloc(snprintf(NULL, 0, "%d Thread sucessfully created ! "\
        "%s %s %s", NO_EVENT, new_thread->base.uuid, new_thread->base.name,
        new_thread->message) + 1)))
        return (EXIT_FAILURE);
    sprintf(event, "%d Thread sucessfully created ! %s %s %s", NO_EVENT,
            new_thread->base.uuid, new_thread->base.name, new_thread->message);
    send_event_to_clients(event, glob, cli->team);
    return (EXIT_SUCCESS);
}

static int add_reply(create_t *create, gthread_t *thread, client_t *cli,
    global_t *glob)
{
    reply_t *new_reply = create_reply(cli->base.name, create->body,
        cli->base.uuid);

    server_event_thread_new_message(thread->base.uuid,
        new_reply->uuid_creator, new_reply->message);
    if (!thread->replies)
        thread->replies = bvector_create(new_reply, REPLY);
    else
        bvector_push_back(thread->replies, new_reply, REPLY);
    return (add_reply_helper(cli, thread, new_reply, glob));
}

int cmd_create(client_t *cli, header_t *header, global_t *glob)
{
    create_t *create = (create_t *)header;

    if (cli->thread) {
        if (create->name[0] != 0 || create->body[0] == 0) {
            dprintf(cli->fd, "%d Too many argument\r\n", NO_EVENT);
            return (EXIT_FAILURE);
        }
        return (add_reply(create, cli->thread, cli, glob));
    }
    if (create->name[0] == 0 || create->body[0] == 0) {
        dprintf(cli->fd, "%d Two argument needed\r\n", NO_EVENT);
        return (EXIT_FAILURE);
    }
    if (cli->channel)
        return (add_thread(create, cli->channel, cli, glob));
    if (cli->team)
        return (add_channel(create, cli->team, cli, glob));
    return (add_team(create, cli, glob));
}