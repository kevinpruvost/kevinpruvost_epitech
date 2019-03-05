/*
** EPITECH PROJECT, 2018
** str_add.c
** File description:
** str_add
*/

char *str_add(char *base, char *toadd)
{
    int i = 0;

    for (; base[i] != 0; i++);
    for (int j = 0; toadd[j] != 0; j++, i++) {
        base[i] = toadd[j];
    }
    return (base);
}
