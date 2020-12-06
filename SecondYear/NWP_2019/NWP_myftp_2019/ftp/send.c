/*
** EPITECH PROJECT, 2020
** send.c
** File description:
** sned
*/

#include "main.h"

const message_t messages[] = {\
{120, "%d Service ready in %s minutes."CRLF, 1}, \
{125, "%d Data connection already open; transfer starting."CRLF, 0}, \
{150, "%d File status okay; about to open data connection."CRLF, 0}, \
{200, "%d Command okay."CRLF, 0}, \
{214, "214-The following commands are recognized.\n"\
" USER PASS CWD CDUP QUIT DELE PWD PASV PORT\n"\
" HELP NOOP RETR STOR LIST\n"\
"%d Help message."CRLF, 0}, \
{220, "%d Service ready for new user."CRLF, 0}, \
{221, "%d Service closing control connection."CRLF, 0}, \
{226, "%d Closing data connection."CRLF, 0}, \
{227, "%d Entering Passive Mode (%s)."CRLF, 1}, \
{230, "%d User logged in, proceed."CRLF , 0}, \
{250, "%d Requested file action okay, completed."CRLF, 0}, \
{257, "%d \"%s\" created."CRLF, 1}, \
{331, "%d User name okay, need password."CRLF, 0}, \
{332, "%d Need account for login."CRLF, 0}, \
{400, "%d Error (RFC compliant)"CRLF, 0}, \
{425, "%d Use PORT or PASV first."CRLF, 0}, \
{500, "%d Unknown command."CRLF, 0}, \
{530, "%d Permission denied."CRLF, 0}, \
{550, "%d Requested action not taken.\n"\
"    File unavailable (e.g., file not found, no access).."CRLF, 0}, \
{0, NULL, 0}\
};

int my_send(int fd, int id, char *arg)
{
    char buffer[BUFFER_SIZE];
    int i = 0;

    memset(buffer, 0, BUFFER_SIZE);
    for (; messages[i].error_code != 0 && messages[i].error_code != id; i++);
    if (messages[i].error_code == 0)
        return EXIT_FAILURE;
    (messages[i].argc != 0) ? \
snprintf(buffer, (BUFFER_SIZE - 1), messages[i].msg, id, arg) : \
snprintf(buffer, (BUFFER_SIZE - 1), messages[i].msg, id);
    if (write(fd, buffer, strlen(buffer)) == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

int my_send_custom(int fd, int id, char * format)
{
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, BUFFER_SIZE);
    for (int j = 0; j < BUFFER_SIZE; buffer[j++] = 0);
    snprintf(buffer, (BUFFER_SIZE - 1), "%d %s\r\n", id, format);
    if (write(fd, buffer, strlen(buffer)) == -1)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}