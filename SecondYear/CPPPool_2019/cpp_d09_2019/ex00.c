/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "ex00.h"

// C++ includes
#include <stdlib.h>
#include <stdio.h>

static void koala_initializer(koala_t *this, char *_name, char _is_A_Legend)
{
    this->m_parent.m_name = _name;
    this->m_is_a_legend = _is_A_Legend;
}

static void cthulhu_initializer(cthulhu_t *this)
{
    printf("----\nBuilding Cthulhu\n");
    this->m_power = 42;
    this->m_name = "Cthulhu";
}

cthulhu_t *new_cthulhu(void)
{
    cthulhu_t *new_oeuf = malloc(sizeof(cthulhu_t));

    if (new_oeuf == NULL)
        return (NULL);
    cthulhu_initializer(new_oeuf);
    return (new_oeuf);
}

void print_power(cthulhu_t *this)
{
    if (this == NULL)
        return;
    printf("Power => %d\n", this->m_power);
}

void attack(cthulhu_t *this)
{
    if (this == NULL)
        return;
    if (this->m_power >= 42) {
        this->m_power -= 42;
        printf("%s attacks and destroys the city\n", this->m_name);
    }
    else
        printf("%s can't attack, he doesn't have enough power\n", this->m_name);
}

void sleeping(cthulhu_t *this)
{
    if (this == NULL)
        return;
    this->m_power += 42000;
    printf("%s sleeps\n", this->m_name);
}

koala_t *new_koala(char * name, char is_a_legend)
{
    koala_t *new_oeuf = malloc(sizeof(koala_t));

    if (new_oeuf == NULL)
        return (NULL);
    cthulhu_initializer(&new_oeuf->m_parent);
    koala_initializer(new_oeuf, name, is_a_legend);
    if (is_a_legend == 0)
        new_oeuf->m_parent.m_power = 0;
    printf("Building %s\n", name);
    return (new_oeuf);
}

void eat(koala_t *this)
{
    if (this == NULL)
        return;

    this->m_parent.m_power += 42;
    printf("%s eats\n", this->m_parent.m_name);
}