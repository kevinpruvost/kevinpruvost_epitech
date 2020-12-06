/*
** EPITECH PROJECT, 2018
** is_alphabet.c
** File description:
** is in alphabet
*/

#include "../../include/my.h"

int is_ltr(char letter)
{
    if (letter >= 'a' && letter <= 'z')
        return (1);
    if (letter >= 'A' && letter <= 'Z')
        return (1);
    return (0);
}
