/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** linux_get_current_path
*/

#include "get_path.h"

/**
 * @brief Get current unix working path
 * 
 * @return char* 
 */
char *linux_get_path()
{
    char * path = malloc(PATH_MAX);

    if (!path)
        return NULL;
    
    memset(path, 0, PATH_MAX);

    if (getcwd(path, PATH_MAX) != NULL)
        return path;
    else
        return NULL;    
    return path;
}

/**
 * @brief free unix pointer
 * 
 * @param path pointer to free
 */
void linux_free_path(char * path)
{
    if (path)
        free(path);
}