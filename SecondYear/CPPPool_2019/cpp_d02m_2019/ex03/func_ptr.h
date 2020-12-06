/*
** EPITECH PROJECT, 2020
** my.h
** File description:
** Header of mylib
*/

#ifndef FUNC_PTR_H

#include "func_ptr_enum.h"

void print_normal(const char *str);
void print_reverse(const char *str);
void print_upper(const char *str);
void print_42(const char *str);

void do_action(action_t action, const char *str);

#endif