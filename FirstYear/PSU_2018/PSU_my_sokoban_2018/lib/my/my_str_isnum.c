/*
** EPITECH PROJECT, 2018
** my_strisnum.c
** File description:
** Function that verify if a string is in the digits.
*/

int my_str_isnum(char const *str)
{
    int isnum = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] > '9' || str[i] < '0')
            isnum = 1;
    }
    if (isnum == 1) {
        return (0);
    } else {
        return (1);
    }
}
