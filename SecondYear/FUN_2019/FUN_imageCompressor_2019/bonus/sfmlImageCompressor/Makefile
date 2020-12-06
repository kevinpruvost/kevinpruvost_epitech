##
## EPITECH PROJECT, 2019
## makefile
## File description:
## g++
##

NAME	= sfmlImageCompressor

CC	= g++

RM	= rm -f

SRCS	= 	main.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -Wall -Wextra
CPPFLAGS += -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
