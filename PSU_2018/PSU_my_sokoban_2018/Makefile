##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	main.c 		\
		error_managing.c	\
		my_sokoban.c	\
		check_win.c	\
		move_player.c	\
		colors.c	\
		check_o.c	\
		help_option.c	\
		main_2.c

BON	=	bonus/main.c          \
                error_managing.c        \
                bonus/my_sokoban.c    \
                check_win.c     \
                move_player.c   \
                colors.c        \
                check_o.c       \
                help_option.c   \
                main_2.c	\
		bonus/main_menu.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_sokoban

all: $(NAME)

$(NAME):
	make -C./lib/my
	$(CC) -g -o $(NAME) $(SRC) -L./lib/my -lmy -I./include/ -lncurses

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME)

re:	fclean all

bonus:	fclean
	make -C./lib/my
	$(CC) -g -o $(NAME) $(BON) -L./lib/my -lmy -I./include/ -lncurses

.PHONY: all clean fclean
