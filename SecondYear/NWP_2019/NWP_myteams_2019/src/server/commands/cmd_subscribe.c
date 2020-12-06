/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** cmd_connect
*/

#include "server.h"

int cmd_subscribe(client_t *cli, header_t *header, global_t *glob)
{
    team_t *team = bvector_get_from_uuid(glob->teams,
                            ((uuidx1_t *)header)->uuid);

    if (!team) {
        dprintf(cli->fd, "%d Team does not exist\r\n",
                                EVENT_ERROR_UNKNOWN_TEAM);
        return (EXIT_FAILURE);
    }
    if (!cli->subs)
        cli->subs = bvector_create(team, TEAM);
    else
        bvector_push_back(cli->subs, team, TEAM);
    server_event_user_join_a_team(team->base.uuid, cli->base.uuid);
    dprintf(cli->fd, "%d Subbed succesfully to: %s\r\n", NO_EVENT,
                                                team->base.name);
    return EXIT_SUCCESS;
}