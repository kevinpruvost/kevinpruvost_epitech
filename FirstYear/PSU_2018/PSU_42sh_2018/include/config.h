/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** The shell configuration file.
*/

#ifndef FORTYTWOSH_CONFIG_H
#define FORTYTWOSH_CONFIG_H

#define EXIT_ERROR (84)

#define COLUMNS (8)
#define DEPTH_MAX (16)

#define COMMAND_SEPARATORS (" \t\v\f")

#define COLOR_RED ("\e[91m")
#define COLOR_BOLD ("\e[1m")
#define COLOR_RESET ("\e[0m")
#define COLOR_GREEN ("\e[92m")
#define COLOR_BRED ("\e[1m\e[91m")
#define COLOR_BGREEN ("\e[1m\e[92m")

#define E_ALIAS_LOOP ("Alias loop")
#define E_NUMBER ("Badly formed number")
#define E_CMD_NOTFOUND ("Command not found")
#define E_BUILTIN_TFARGS ("Too few arguments")
#define E_BUILTIN_TMARGS ("Too many arguments")
#define E_ENV_UNKNOWN ("Failed to set variable")
#define E_CHDIR_HOME ("Can't change to home directory")
#define E_ENV_SWLETTER ("Variable name must begin with a letter")
#define E_ENV_ALPHANUM ("Variable name must contain alphanumeric characters")

#endif
