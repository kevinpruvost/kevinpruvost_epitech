/*
** EPITECH PROJECT, 2020
** r-type
** File description:
** get_path
*/

#pragma once

#ifdef __unix__
    #include <stddef.h>
    #include <stdlib.h>
    #include <linux/limits.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
#elif _WIN32
    #include <stdio.h>
    #include <conio.h>
    #include <stdlib.h>
    #include <direct.h>
    #include <string.h>
#endif