/*
** EPITECH PROJECT, 2018
** test_criterion
** File description:
** for criterion test BSQ
*/

#include <criterion/criterion.h>
#include "../include/my.h"
#include "../../include/my.h"

Test(Test11, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_100_100";
    char *file = "tests/maps/intermediate_map_100_100";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test12, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_200_200";
    char *file = "tests/maps/intermediate_map_200_200";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test13, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_500_500";
    char *file = "tests/maps/intermediate_map_500_500";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test14, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_500_500_2";
    char *file = "tests/maps/intermediate_map_500_500_2";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test15, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_500_500_3";
    char *file = "tests/maps/intermediate_map_500_500_3";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}
