##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	Sfml.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ArcadeContent.cpp \
			../../include/SpriteData.cpp \
			../../include/ADisplayModule.cpp \
			../../include/AModule.cpp \
			../../include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_sfml.so

CXX         =	g++
CXXFLAGS    =	-I./ -I../../include -fPIC -pipe -g -Wall
CXXFLAGS	+=	-lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
