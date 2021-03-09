/*
** EPITECH PROJECT, 2018
** mysh
** File description:
** Create a new environment variable instance.
*/

#include <string.h>
#include <stdlib.h>

char *sh_newenv(const char *key, const char *value)
{
    size_t lkey = 0;
    char *env = NULL;
    size_t lvalue = 0;

    if (key == NULL)
        return NULL;
    if (value == NULL)
        value = (char []) {'\0'};

    lkey = strlen(key);
    lvalue = strlen(value);

    if ((env = malloc(lkey + lvalue + 2)) == NULL)
        return NULL;

    strcpy(env, key);
    strcat(env, "=");
    strcat(env, value);

    return env;
}
