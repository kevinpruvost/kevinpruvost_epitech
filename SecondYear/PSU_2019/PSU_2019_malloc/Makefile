##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC 	=   malloc.c \
			mem_struct.c \
			free_brk.c \
			realloc_brk.c \
			my_sbrk.c \
			add_mem.c \
			next.c \
			base_mem.c \
			#$(wildcard my_printf/*.c) \

SRCTEST	=	main.c \

OBJ		=	$(SRC:.c=.o)

OBJTEST	=	$(SRCTEST:.c=.o)

NAME	=	libmy_malloc.so

CC      =	gcc

CFLAGS    =	-pipe -g -Wall -W -fPIC -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) -shared -fPIC

clean:
	rm -f $(OBJ) test
	rm -f *.o

fclean: clean
	rm -f $(NAME) vgcore.*

test: $(NAME) $(OBJTEST)
	@$(CC) $(CFLAGS) -o test $(OBJTEST) -L. -lmy_malloc
	clear
	LD_LIBRARY_PATH=$(PWD) LD_PRELOAD=$(NAME) ./test

vtest:
	clear
	LD_LIBRARY_PATH=$(PWD) LD_PRELOAD=$(NAME) valgrind -v ./test

re: fclean all

.PHONY: clean re fclean all
