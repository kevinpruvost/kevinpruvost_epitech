/*
** EPITECH PROJECT, 2018
** my_atoi.c
** File description:
** like my_get_nbr
*/

int my_atoi(char *str)
{
    int number = 0;
    int j;
    int mult = 1;
    int negative = 0;

    if (str[0] == '-') {
        str++;
        negative = 1;
    }
    for (j = 0; str[j+1] != 0; j++)
        if (str[j] < '0' || str[j] > '9')
            return (0);
    for (int i = j; i >= 0; i--) {
        number += (str[i] - 48) * mult;
        mult *= 10;
    }
    if (negative == 1)
        number *= -1;
    return (number);
}
