#include "my.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i] != 0; i++);
    return (i);
}

void my_putstr(char *str)
{
    int nb = my_strlen(str);

    write(1, str, nb);
}

int my_put_nbr(int nb)
{
    int reste = 0;
    char *nbr = malloc(sizeof(char) * 13);
    int n = 0;

    if (nb == 0)
        my_putchar('0');
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    }
    for (int i = 0; nb > 0; i++) {
	reste = nb % 10;
        nbr[i] = reste + 48;
        nb = (nb - reste) / 10;
        n++;
    }
    for (int i = n-1; i >= 0; i--)
        my_putchar(nbr[i]);
    free(nbr);
    return (0);
}
