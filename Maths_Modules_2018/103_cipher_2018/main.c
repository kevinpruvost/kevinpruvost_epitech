/*
** EPITECH PROJECT, 2018
** 103cipher
** File description:
** 
*/

#include "my.h"
#include <stdlib.h>

int main(int n, char **arg)
{
    if (n == 2) {
        printf("USAGE\n"
               "    ./103cipher message key flag\n\n"
               "DESCRIPTION\n    message     a message, made of ASCII characters\n"
               "    key         the encryption key, made of ASCII characters\n"
               "    flag        0 for the message to be encrypted, 1 to be decryped\n");
        return (84);
    }
    if (n != 4 || (arg[3][0] != '0' && arg[3][0] != '1') || arg[3][1] != '\0')
        return (84);
    if (arg[3][0] == '0')
        crypt(arg[1], arg[2]);
    if (arg[3][0] == '1')
        decrypt(arg[1], arg[2]);
    return (0);
}
