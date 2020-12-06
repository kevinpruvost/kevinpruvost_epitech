/*
** EPITECH PROJECT, 2020
** rfc_filtering.c
** File description:
** rfc
*/

#include "client.h"

static int extract_code(char ** line)
{
    int code = EXIT_FAILURE;
    char c[3] = {0, 0, 0};

    if (!isdigit((*line)[0]))
        return EXIT_FAILURE;
    get_last_reponse(*line);
    for (int i = 0; i < 3 && isdigit((*line)[0]); ++i) {
        c[i] = (*line)[0];
        ++(*line);
    }
    if (!isspace((*line)[0]))
        return EXIT_FAILURE;
    ++(*line);
    code = atoi(c);
    return code;
}

int rfc_filtering(char * line, account_t * account)
{
    int code = extract_code(&line);

    if (code == EXIT_FAILURE)
        return EXIT_FAILURE;
    treat_code(code, account, line);
    return EXIT_SUCCESS;
}