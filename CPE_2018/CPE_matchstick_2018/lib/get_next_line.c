/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** main functions
*/

#include "my.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *my_stradd(char *dest, char *src)
{
    int i = 0;
    char *new;

    new = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + 1));
    if (new == NULL)
        return (NULL);
    if (src[0] == 0)
        return (new);
    for (i = 0; dest[i] != 0; i++)
        new[i] = dest[i];
    for (int j = 0; src[j] != 0; i++, j++)
        new[i] = src[j];
    new[i] = '\0';
    free(dest);
    return (new);
}

char *read_file(int fd, char *content)
{
    char buffer[READ_SIZE + 1];
    int error = 1;

    if (content != NULL) {
        free(content), content = malloc(sizeof(char));
    } else
        content = malloc(sizeof(char));
    if (read(fd, buffer, READ_SIZE) <= 0 || READ_SIZE == 0 || content == NULL)
        return (NULL);
    for (; error != -1; read(fd, buffer, READ_SIZE)) {
        buffer[READ_SIZE] = '\0';
        (buffer[0] != 0) ? (content = my_stradd(content, buffer)) : (0);
        for (int i = 0; i < READ_SIZE; i++) {
            (buffer[i] == '\n' || buffer[i] == 0) ? (error = -1) : (0);
            buffer[i] = 0;
        }
        if (error == -1) break;
    }
    return (content);
}

char *get_next_line2(char *line, char *cnt)
{
    int character = 0;

    line = malloc(sizeof(char) * (my_strlen(cnt) + 1));
    if (line == NULL)
        return (NULL);
    for (int i = character, j = 0; cnt[i] != '\0' && cnt[i] != '\n'; i++, j++) {
        line[j] = cnt[i];
        line[j+1] = '\0';
    }
    if (cnt[0] == '\n')
        line = "\n\0";
    return (line);
}

char *get_next_line(int fd)
{
    static char *cnt;
    static int fd_moment = -1;
    char *line;

    if (fd == -1)
        return (NULL);
    if (cnt == NULL || fd_moment == -1 || fd_moment != fd) {
        cnt = read_file(fd, cnt);
        fd_moment = fd;
    }
    if (cnt == NULL)
        return (NULL);
    line = get_next_line2(line, cnt);
    for (; cnt[0] != '\n' && cnt[0] != 0; cnt++)
        (cnt[0] == '\n') ? (cnt++) : (0);
    (cnt[0] == 0 || fd == 0) ? (cnt = NULL) : (0);
    (line[0] == 0) ? (line = NULL) : (0);
    return (line);
}
