/*
** EPITECH PROJECT, 2020
** tools.c
** File description:
** tools
*/

#include "main.h"

bool starts_with(const char *pre, const char *str)
{
    size_t lenpre = strlen(pre);
    size_t lenstr = strlen(str);

    return lenstr > lenpre ? false : memcmp(pre, str, lenstr) == 0;
}

bool ends_with(char * base, char * str)
{
    int blen = strlen(base);
    int slen = strlen(str);

    return (blen > slen) && (0 == strcmp(base + blen - slen, str));
}

int is_numeric(const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
        return 0;
    char * p;
    strtod(s, &p);
    return *p == '\0';
}

char ** split(char * line, const char * delimiter)
{
    char * token = multi_tok(line, delimiter);
    char ** res = NULL;

    if (line == NULL || token == NULL)
        return NULL;
    res = malloc(sizeof(char *));
    for (int tabsize = 1; token != NULL;) {
        res = realloc(res, sizeof(char *) * (tabsize + 1));
        res[tabsize - 1] = strdup(token);
        res[tabsize++] = NULL;
        free(token);
        token = multi_tok(NULL, delimiter);
    }
    return res;
}

void free_2darray(void ** array)
{
    for (int i = 0; array[i] != NULL; ++i) {
        free(array[i]);
    }
    free(array);
}