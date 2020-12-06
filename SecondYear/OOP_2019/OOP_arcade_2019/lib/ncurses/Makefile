##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	Ncurses.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ArcadeContent.cpp \
			../../include/SpriteData.cpp \
			../../include/ADisplayModule.cpp \
			../../include/AModule.cpp \
			../../include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_ncurses.so

CXX         =	g++ -lm
CXXFLAGS    =	-I./ -I../../include -fPIC -pipe -g -Wall -lncurses

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
