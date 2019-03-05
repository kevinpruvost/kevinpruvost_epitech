##
## EPITECH PROJECT, 2018
## Makefile DOOP
## File description:
## Makefile for DOOP
##

CRTEST	=	./tests/cr_test.c

CC	 =	gcc

NAME	=	my_printf

all: $(NAME)

$(NAME):
	make -C./lib/my

clean:
	make clean -C./lib/my

fclean: clean
	make fclean -C./lib/my
	rm -f $(NAME)

criterion:
	make -C./lib/mu
	$(CC) -g -o $(NAME) $(SRC) -L./lib/my -lmy -I./include/ $(CRTEST) --coverage -lcriterion

re:	fclean all

.PHONY: all clean fclean
