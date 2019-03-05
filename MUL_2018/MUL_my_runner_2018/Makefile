##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	main.c				\
		window_prop.c			\
		my_runner.c			\
\
		shrekometry_dash/main.c		\
		shrekometry_dash/vars.c		\
		shrekometry_dash/free.c		\
		shrekometry_dash/vars2.c	\
		shrekometry_dash/jump.c		\
		shrekometry_dash/elements.c	\
\
		menu/main.c			\
		menu/vars.c			\
		menu/processes.c		\
\
		objects/sound_object.c          \
                objects/player_object.c         \
                objects/background_object.c     \
                objects/game_object.c           \
                objects/text_object.c           \
\
		lib/my_atoi.c			\
		lib/my_putstr.c			\
		lib/my_strlen.c			\
		lib/my_getfloat.c		\
		lib/my_getnbr.c			\
		lib/my_revstr.c			\
		lib/str_add.c			\
		lib/load_file_in_mem.c		\
\
		csfml/basic_functions.c		\

NAME	=	my_runner

all:
	gcc $(SRC) -o $(NAME) -l csfml-window -l csfml-graphics -l csfml-system -l csfml-audio -I./include -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
