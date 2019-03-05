/*
** EPITECH PROJECT, 2018
** my_put_nbrhexa.c
** File description:
** my_put_nbrhexa.c
*/

#include "../../include/my.h"

void my_put_nbrhexa(unsigned int nbr)
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
    my_putstr(final);
    free(final);
}

void my_put_nbrocta(unsigned int nbr)
{
    char *final = malloc(sizeof(char) * sizeof(nbr));
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 8;
        nbr /= 8;
        final[i] = reste + 48;
    }
    my_revstr(final);
    my_putstr(final);
    free(final);
}

void my_put_adress(void *adress)
{
    long int nbr = (long int)adress;
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
    my_putstr("0x");
    my_putstr(final);
    free(final);

}

void my_put_nbrunsigned(int nbr)
{
    if (nbr < 0)
        nbr *= (-1);
    my_put_nbr(nbr);
}

void my_put_unsigned_binary(int nbr)
{
    char *final = malloc(sizeof(char) * sizeof(nbr));
    int reste = 0;

    for (int i = 0; nbr > 0; i++) {
        reste = nbr % 2;
        nbr /= 2;
        final[i] = reste + 48;
    }
    my_revstr(final);
    my_putstr(final);
    free(final);
}
