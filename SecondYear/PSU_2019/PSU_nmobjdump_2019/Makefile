##
## EPITECH PROJECT, 2020
## Make file
## File description:
## clean rule
##

SRC1 	=   nm/main.c \
			nm/nm.c \
			nm/get_symbols.c \
			nm/read.c \
			nm/type.c \
			nm/sort.c \
			nm/pre_open.c \

SRC2 	=   objdump/main.c \
			objdump/objdump.c \
			objdump/get_symbols.c \
			objdump/read.c \
			objdump/sort.c \
			objdump/header.c \
			objdump/tools.c \
			objdump/read_section.c \

OBJ1	=	$(SRC1:.c=.o)
OBJ2	=	$(SRC2:.c=.o)

NAME1	=	my_nm
NAME2	=	my_objdump

CC      =	gcc
CFLAGS  =	-I./include -pipe -g -Wall -W -Iinclude -ldl

all: nm objdump

nm: $(OBJ1)
	$(CC) $(OBJ1) $(CFLAGS) -o $(NAME1)

objdump: $(OBJ2)
	$(CC) $(OBJ2) $(CFLAGS) -o $(NAME2)

clean:
	rm -f $(OBJ1) $(OBJ2)
	rm -f *.o

fclean: clean
	rm -f vgcore.*
	rm -f $(NAME1) $(NAME2)

#test: $(NAME) $(OBJTEST)
#	@$(CC) $(CFLAGS) -o test $(OBJTEST) -L. -lmy_malloc
#	clear
#	LD_LIBRARY_PATH=$(PWD) LD_PRELOAD=$(NAME) ./test

re: fclean all

.PHONY: clean re fclean all
