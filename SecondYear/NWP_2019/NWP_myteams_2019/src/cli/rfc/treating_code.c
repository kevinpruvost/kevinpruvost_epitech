/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** string_utils
*/

#include "client.h"

const treat_code_t funcs[] = {\
{EVENT_LOGGEDIN, &event_loggedin}, \
{EVENT_LOGGEDOUT, &event_loggedout}, \
{EVENT_MP_RECEIVED, &event_mp_received}, \
{EVENT_THREAD_MSG_RECEIVED, &event_thread_msg_received}, \
{EVENT_PRINT_USERS, &event_print_users}, \
{EVENT_PRINT_TEAMS, &event_print_teams}, \
{EVENT_TEAM_PRINT_CHANNELS, &event_team_print_channels}, \
{EVENT_CHANNEL_PRINT_THREADS, &event_channel_print_thread}, \
{EVENT_THREAD_PRINT_REPLIES, &event_thread_print_replies}, \
{EVENT_MP_PRINT_MSG, &event_mp_print_msg}, \
{EVENT_ERROR_UNKNOWN_TEAM, &event_unknown_team}, \
{EVENT_ERROR_UNKNOWN_CHANNEL, &event_unknown_channel}, \
{EVENT_ERROR_UNKNOWN_THREAD, &event_unknown_thread}, \
{EVENT_ERROR_UNKNOWN_USER, &event_unknown_user}, \
{EVENT_ERROR_UNAUTHORIZED, &event_unauthorized}, \
{NO_EVENT, &event_no_event}, \
{EXIT_FAILURE, NULL}\
};

char * get_last_reponse(char * line)
{
    static char buffer[4096] = {0};
    char * temp = NULL;

    if (line == NULL) {
        temp = strdup(buffer);
        memset(buffer, 0, 4096);
        return temp;
    } else {
        memset(buffer, 0, 4096);
        strcpy(buffer, line);
        return NULL;
    }
}

void treat_code(int code, account_t * account, char * line)
{
    char ** tab = split_no_delim(line, " : ");
    char * new_line = NULL;

    for (int i = 0; funcs[i].ptr != NULL; ++i) {
        if (code == funcs[i].code) {
            new_line = funcs[i].ptr(line, account, tab);
            break;
        }
    }
    printf("[SERVER] > %s\n", new_line);
    free(new_line);
    free_2darray((void **)tab);
}