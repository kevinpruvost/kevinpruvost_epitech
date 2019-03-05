/*
** EPITECH PROJECT, 2018
** my_getnbrforprintf.c
** File description:
** gets nbr for my_printf
*/

#include "../../include/my.h"

char *my_get_nbrhexa(unsigned int nbr)
{
    char *final = malloc(sizeof(char) * sizeof(nbr));
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 16;
        nbr /= 16;
        if (reste <= 9 && reste >= 0)
            final[i] = reste + 48;
        if (reste >= 10 && reste <= 16)
            final[i] = reste + 55 + 32;
    }
    my_revstr(final);
    return (final);
}

char *my_get_nbrocta(unsigned int nbr)
{
    char *final = malloc(sizeof(char) * sizeof(nbr));
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 8;
        nbr /= 8;
        final[i] = reste + 48;
    }
    my_revstr(final);
    return (final);
}

char *my_get_adress(void *adress)
{
    long int nbr = (long int)adress;
    char *final = malloc(sizeof(char) * 28);
    char *final2 = malloc(sizeof(char) * 28);
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 16;
        nbr /= 16;
        if (reste <= 9 && reste >= 0)
            final[i] = reste + 48;
        if (reste >= 10 && reste <= 16)
            final[i] = reste + 55 + 32;
    }
    my_revstr(final);
    final2[0] = '0';
    final2[1] = 'x';
    for (int i = 2, j = 0; final[j] != 0; i++, j++)
        final2[i] = final[j];
    free(final);
    return (final2);
}

char *my_get_unsigned_binary(int nbr)
{
    char *final = malloc(sizeof(char) * sizeof(nbr));
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 2;
        nbr /= 2;
        final[i] = reste + 48;
    }
    my_revstr(final);
    return (final);
}
