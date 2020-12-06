##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC =	main.cpp \

OBJ = $(SRC:.cpp=.o)

NAME =	my_cat

CC 		= 	g++

CFLAGS	=	-fno-builtin -std=gnu11 -Wall -Wextra -g

all: $(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean: 
	rm -f $(OBJ) $(OBJTEST)

fclean: clean
	rm -f $(NAME) $(NAMETEST) vgcore.*

re: fclean all