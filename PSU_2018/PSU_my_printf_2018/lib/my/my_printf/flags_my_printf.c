/*
** EPITECH PROJECT, 2018
** flags_my_printf.c
** File description:
** flags management
*/

#include "include/my.h"
#include <stdarg.h>

void final_print1(char ids, char *str, va_list *vars)
{
    switch (ids) {
    case ('c'):
        case_c(va_arg(*vars, int), str);
        break;
    case ('s'):
        if (str[0] != '%')
            my_putstr(str);
        else
            case_s(va_arg(*vars, char *), str);
        break;
    case ('d'): case('i'):
        case_di(va_arg(*vars, int), str);
        break;
    case('%'):
        my_putchar('%');
        break;
    case('x'): case('X'):
        case_x(va_arg(*vars, unsigned int), str, ids);
        break;
    }
}

void final_print2(char ids, char *str, va_list *vars)
{
    switch (ids) {
    case('o'):
        case_o(va_arg(*vars, unsigned int), str);
        break;
    case('u'):
        case_u(va_arg(*vars, int), str);
        break;
    case('p'):
        case_p(va_arg(*vars, void *), str);
        break;
    case('b'):
        case_b(va_arg(*vars, unsigned int), str);
        break;
    case('S'):
        case_spec(va_arg(*vars, char *), str);
        break;
    case('f'):
        case_f(va_arg(*vars, double), str);
        break;
    }
}

void my_flags_printf(char ids, char *str, va_list *vars)
{
    final_print1(ids, str, vars);
    final_print2(ids, str, vars);
}
