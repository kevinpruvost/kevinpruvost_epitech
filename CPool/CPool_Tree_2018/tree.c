/*
** EPITECH PROJECT, 2018
** tree.c
** File description:
** Function that displays a tree.
*/

int getmax(int size)
{
    int nb = 3;
    int etage2 = 1;
    int twotimes = (-1);

    for (int i = 0; i != size; i++) {
        nb = nb + (0 + ((3 + i) * 2));
        nb = nb - (2 * etage2);
        twotimes++;
        if (twotimes == 2) {
            twotimes = 0;
            etage2++;
        }
    }
    return (nb);
}

int largeuretage(int etage, int size)
{
    int nb = 1;
    int twotimes = 0;
    int twotimesmax = 4;
    int twotwo = 0;
    int etage2 = 2;

    for (; etage != 1; etage--) {
        twotimes++;
        nb = nb + 2;
    if (twotimes == twotimesmax) {
            twotimesmax++;
            twotimes = 0;
            twotwo++;
            nb = nb - (2 * etage2);
        }
        if (twotwo == 2) {
            etage2++;
            twotwo = 0;
        }
    }
    return (nb);
}

void body(int sizemax, int ecartmax, int size)
{
    int ecart = 0;
    int sizebase = 1;
    int etage = 1;
    int nbetage;
    int largeur = 0;

    for (int i = 0; i != size; i++) {
        nbetage = nbetage + 4 + i;
    }
    if (size % 2 == 0)
        nbetage--;
    for (;etage  <= nbetage; etage++) {
        largeur = largeuretage(etage, size);
        for (ecart = (largeur - 1) / 2; ecart < ecartmax; ecart++) {
            my_putchar(' ');
        }
        for (; largeur != 0; largeur--) {
            my_putchar('*');
        }
        my_putchar('\n');
    }
}

void base(int size, int ecartbase, int ecartmax, int bodysize)
{
    if (size == 1) {
        bodysize = 1;
    } else if ( (size % 2) == 1) {
        bodysize = size;
    } else {
        bodysize = size + 1;
    }
    int ecartdebut = ecartbase;
    int bodydebut = bodysize;

    for (; size != 0; size--) {
        ecartbase = ecartdebut;
        for (; ecartbase > 0; ecartbase--) {
            my_putchar(' ');
        }
        bodysize = bodydebut;
        for (; bodysize > 0; bodysize--) {
            my_putchar('|');
        }
        my_putchar('\n');
    }
}

void tree(int size)
{
    int sizemax = getmax(size);
    int ecartmax = (sizemax - 1) / 2;
    int ecartbase = ecartmax - (size / 2);
    int bodysize;

    if (size <= 0) {
    } else {
        body(sizemax, ecartmax, size);
        base(size, ecartbase, ecartmax, bodysize);
    }
}
