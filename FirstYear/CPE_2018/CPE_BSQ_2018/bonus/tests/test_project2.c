/*
** EPITECH PROJECT, 2018
** test_criterion
** File description:
** for criterion test BSQ
*/

#include <criterion/criterion.h>
#include "../include/my.h"
#include "../../include/my.h"

Test(Test6, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_34_137_with_obstacles_25pc";
    char *file = "tests/maps/intermediate_map_34_137_with_obstacles_25pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test7, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_34_137_with_obstacles_50pc";
    char *file = "tests/maps/intermediate_map_34_137_with_obstacles_50pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test8, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_34_137_with_obstacles_75pc";
    char *file = "tests/maps/intermediate_map_34_137_with_obstacles_75pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test9, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_34_137_empty";
    char *file = "tests/maps/intermediate_map_34_137_empty";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test10, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_34_137_filled";
    char *file = "tests/maps/intermediate_map_34_137_filled";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}