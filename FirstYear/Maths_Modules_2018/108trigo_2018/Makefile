##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC		=	src/main.c				\
			src/calculs.c				\
			src/tools.c				\
			src/print_matrix.c			\
			src/create_matrix.c			\
			src/mult_matrice.c			\

NAME		=	108trigo

all:	$(NAME)

$(NAME):
	gcc -I include -g $(SRC) -o $(NAME) -lm

.PHONY: clean fclean

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all
