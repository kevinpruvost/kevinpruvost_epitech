##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	main.c 		\
		find_bsq.c	\
		rewrite_map.c	\
		load_array.c

OBJ	=	$(SRC:.c=.o)

NAME	=	bsq

all: $(NAME)

$(NAME):
	make -C./lib/my
	$(CC) -g -o $(NAME) $(SRC) -L./lib/my -lmy -I./include/

clean:
	make clean -C./lib/my
	rm -f $(OBJ)

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
