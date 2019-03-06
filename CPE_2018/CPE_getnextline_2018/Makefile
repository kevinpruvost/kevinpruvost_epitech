##
## EPITECH PROJECT, 2018
## makefile
## File description:
## ah
##

SRC	=	get_next_line.c			\
		utilities.c			\
		main.c

SRC_B	=	a/get_next_line.c		\
		utilities.c			\
		main.c

BON	=	bonus/main.c

NAME	=	gnl

all:
	gcc $(SRC) -o $(NAME) -Wall -Wextra -g -I./

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

bonus:	fclean
	gcc $(BON) -o $(NAME)

.PHONY: all clean fclean
