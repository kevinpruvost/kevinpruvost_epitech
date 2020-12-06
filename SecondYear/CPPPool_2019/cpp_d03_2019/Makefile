##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC =	string0.c \
		string1.c \
		string2.c \
		string3.c \
		my_strcmp.c \
		string4.c \
		string5.c \
		string6.c

SRCTEST	=	main.c

OBJ = $(SRC:.c=.o)

OBJTEST = $(SRCTEST:.c=.o)

NAME = libstring.a

NAMETEST	=	test

CFLAGS	=	-lstring -L./ -fno-builtin -std=gnu11 -Wall -Wextra -g

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc -o $(NAME) $(OBJ)

clean: 
	rm -f $(OBJ) $(OBJTEST)

fclean: clean
	rm -f $(NAME) $(NAMETEST) vgcore.*

test:	all
	@$(CC) -o $(NAMETEST) $(SRCTEST) $(CFLAGS)
	@echo -e "Compilation finished.\n\n---------------------\n"
#	@./$(NAMETEST)
	@valgrind -v --leak-check=full ./$(NAMETEST)

re: fclean all