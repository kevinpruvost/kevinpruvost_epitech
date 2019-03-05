##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CC	 =	gcc

SRC	=	maincr.c 		\
		../find_bsq.c	\
		../rewrite_map.c	\
		../load_array.c

OBJ	=	$(SRC:.c=.o)

GCDA	=	$(SRC:.c=.gcda)

GCNO	=	$(SRC:.c=.gcno)

NAME	=	bonus

all: $(NAME)

test1:
	$(CC) -g -o $(NAME) $(SRC) tests/test_project1.c -L../lib/my -lmy -I../include/ --coverage -lcriterion

test2:
	$(CC) -g -o $(NAME) $(SRC) tests/test_project2.c -L../lib/my -lmy -I../include/ --coverage -lcriterion

test3:
	$(CC) -g -o $(NAME) $(SRC) tests/test_project3.c -L../lib/my -lmy -I../include/ --coverage -lcriterion

$(NAME):
	make -C../lib/my

clean:
	make clean -C../lib/my
	rm -f $(OBJ) $(GCDA) $(GCNO)
	rm -f *.gcda *.gcno

fclean: clean
	make fclean -C../lib/my
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean
