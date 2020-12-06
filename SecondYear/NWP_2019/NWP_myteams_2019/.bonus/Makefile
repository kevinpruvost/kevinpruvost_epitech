##
## EPITECH PROJECT, 2020
## Make file
## File description:
## clean rule
##

SRC		=	$(wildcard *.cpp) \
			$(wildcard client/*.cpp) \

SRC2	=	$(wildcard ../src/cli/**/*.c) \
			../src/cli/read_server_and_client.c \
			../src/cli/read.c \
			../src/cli/socket.c \
			$(wildcard ../src/common/*.c) \

OBJ		=	$(SRC2:.c=.o) $(SRC:.cpp=.o)

NAME	=	../myteams_cli

CC		=	gcc
CFLAGS	=	-I../ -I../include/ -I../libs/ -g -Wall -luuid
CFLAGS 	+= 	-iquote ../libs/myteams/
LDFLAGS += 	-lmyteams -L../libs/myteams/ -L../libs/

CXX         =	g++
CXXFLAGS    =	-std=gnu++11 -I./ -I./client/
CXXFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread
CXXFLAGS 	+=	$(CFLAGS)
CXXFLAGS	+=	$(LDFLAGS)

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
