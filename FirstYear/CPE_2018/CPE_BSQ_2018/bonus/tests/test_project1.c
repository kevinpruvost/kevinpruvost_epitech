/*
** EPITECH PROJECT, 2018
** test_criterion
** File description:
** for criterion test BSQ
*/

#include <criterion/criterion.h>
#include "../include/my.h"
#include "../../include/my.h"

Test(Test1, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_97_21_with_obstacles_25pc";
    char *file = "tests/maps/intermediate_map_97_21_with_obstacles_25pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test2, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_97_21_with_obstacles_50pc";
    char *file = "tests/maps/intermediate_map_97_21_with_obstacles_50pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test3, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_97_21_with_obstacles_75pc";
    char *file = "tests/maps/intermediate_map_97_21_with_obstacles_75pc";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test4, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_97_21_empty";
    char *file = "tests/maps/intermediate_map_97_21_empty";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}

Test(Test5, string)
{
    char *filev;
    filev = "tests/maps_solved/intermediate_map_97_21_filled";
    char *file = "tests/maps/intermediate_map_97_21_filled";
    char *verified = load_file_in_mem1(filev);
    char *toverify = test_cr(file);

    cr_assert_str_eq(toverify, verified);
}