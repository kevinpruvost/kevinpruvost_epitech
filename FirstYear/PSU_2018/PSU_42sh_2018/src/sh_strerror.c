/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** Get an PRINT message by its code.
*/

#include <string.h>

#include "types.h"
#include "config.h"

static const message_t errors[] = {
    ADD_MSG(ENOENT, E_CMD_NOTFOUND),
    ADD_MSG(ENOEXEC, "Exec format error. Wrong Architecture"),
    END_MSG()
};

char *sh_strerror(int errnum)
{
    for (size_t i = 0; errors[i].value != NULL; i++) {
        if (errors[i].code == errnum)
            return (char *) errors[i].value;
    }

    return strerror(errnum);
}
