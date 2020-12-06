/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#include "string.h"

#include <stdlib.h>
#include <string.h>

void string_init2(string_t *this)
{
    this->append_c = &append_c;
    this->at = &at;
    this->clear = &clear;
    this->size = &size;
    this->compare_s = &compare_s;
    this->compare_c = &compare_c;
    this->copy = &copy;
    this->c_str = &c_str;
    this->empty = &empty;
    this->find_s = &find_s;
    this->find_c = &find_c;
    this->insert_c = &insert_c;
    this->insert_s = &insert_s;
    this->to_int = &to_int;
    this->split_s = &split_s;
    this->split_c = &split_c;
    this->print = &print;
    this->join_c = &join_c;
    this->join_s = &join_s;
    this->substr = &substr;
}

void string_init(string_t *this, const char *s)
{
    if (s == NULL)
        this->str = NULL;
    else
        this->str = my_strdup(s);
    this->assign_s = &assign_s;
    this->assign_c = &assign_c;
    this->append_s = &append_s;
    string_init2(this);
}

void string_destroy(string_t *this)
{
    if (this == NULL)
        return;

    free(this->str);
    this->str = NULL;
}

void assign_s(string_t *this, const string_t *str)
{
    if (this == NULL || str == NULL)
        return;
    this->assign_c(this, str->str);
}

void assign_c(string_t *this, const char *s)
{
    if (this == NULL)
        return;
    if (this->str != NULL)
        free(this->str);

    if (s == NULL)
        this->str = NULL;
    else
        this->str = my_strdup(s);
}