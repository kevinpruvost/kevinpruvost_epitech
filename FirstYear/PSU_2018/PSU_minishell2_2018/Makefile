##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## makefile
##

SRC	=	$(wildcard *.c)		\
\
		$(wildcard lib/*.c)	\

NAME    =       mysh

all:
	@gcc $(SRC) -o $(NAME) -I./include -g

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean
