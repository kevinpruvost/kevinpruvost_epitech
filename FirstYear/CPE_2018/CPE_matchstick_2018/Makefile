##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	matchstick.c		\
		print_game_board.c	\
		interaction.c		\
		match_utilities.c	\
		ai.c			\
		ai2.c			\
		ai3.c			\
		ai4.c			\
		display_utilities.c	\
		free.c			\
\
		lib/my_putstr.c		\
		lib/my_strlen.c		\
		lib/my_getfloat.c	\
		lib/my_getnbr.c		\
		lib/my_revstr.c		\
		lib/str_add.c		\
		lib/my_put_nbr.c	\
		lib/my_putchar.c	\
		lib/get_next_line2.c	\
		lib/my_pow.c		\

NAME	=	matchstick

all:
	gcc $(SRC) -o $(NAME) -I./include -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
