##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	window.c	\
		lib/my_atoi.c	\
		lib/my_putstr.c	\
		lib/my_strlen.c	\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_revstr.c		\
		lib/str_add.c		\
		utilities.c	\
		background.c	\
		events.c	\
		duck.c		\
		player.c	\
		csfml/basic_functions.c	\
		shooting_system.c	\
		main_menu.c		\
		lib/load_file_in_mem.c	\
		window_complements.c	\
		set_vars.c		\
		window_processes.c

NAME	=	my_hunter

all:
	gcc $(SRC) -o $(NAME) -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
