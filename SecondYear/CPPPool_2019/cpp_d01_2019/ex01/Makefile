##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

NAME2	=	menger

SRC2	=	main.c \
			menger.c

OBJ2 =	$(SRC2:.c=.o)

CC	=	@gcc

CFLAGS	=	-I./ -Wall -Wextra -O2 -g

all:	run

run:	$(OBJ2)
	$(CC) -o $(NAME2) $(OBJ2) $(CFLAGS)

clean:
	rm -f $(OBJ2) $<

fclean:	clean
	rm -f $(NAME2)

re:	fclean all

.PHONY:	all clean fclean re lib
