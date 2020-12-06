##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

NAME	=	z

SRC 	=	z.c

OBJ	=	$(SRC:.c=.o)

CC	=	@gcc

CFLAGS	=	-I./ -Wall -Wextra -O2 -g

all:	run

run:	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ) $<

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re lib
