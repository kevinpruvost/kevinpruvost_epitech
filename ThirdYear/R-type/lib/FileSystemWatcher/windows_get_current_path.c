/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** windows_get_current_path
*/

#include "get_path.h"

/**
 * @brief Get current windows working path
 * 
 * @return char* 
 */
char *windows_get_path()
{
    char * full = malloc(_MAX_PATH);

    if (!full)
        return NULL;

    memset(full, 0, _MAX_PATH);

    if ( _fullpath( full, "./", _MAX_PATH ) != NULL )
        return full;
    else
        return NULL;
    return full;
}

/**
 * @brief free windows pointer
 * 
 * @param path pointer to free
 */
void windows_free_path(char * path)
{
    if (path)
        free(path);
}