/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** channel_list
*/

#include "server.h"

channel_t * create_channel(char name[MAX_NAME_LENGTH],
                char description[MAX_DESCRIPTION_LENGTH])
{
    channel_t * channel = malloc(sizeof(channel_t));
    uuid_t binuuid;

    uuid_generate_random(binuuid);
    uuid_unparse(binuuid, channel->base.uuid);
    strcpy(channel->base.name, name);
    strcpy(channel->description, description);
    channel->threads = NULL;
    return (channel);
}

void destroy_channel(channel_t * channel)
{
    if (!channel)
        return;
    free(channel);
}