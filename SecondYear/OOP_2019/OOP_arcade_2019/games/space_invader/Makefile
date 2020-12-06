##
## EPITECH PROJECT, 2018
## Make file
## File description:
## clean rule
##

SRC		= 	Menu.cpp \
			NamePanel.cpp \
			SpaceInvader.cpp \
			Player.cpp \
			Ennemy.cpp \
			Bridge.cpp \
			../../include/ArcadeEvent.cpp \
			../../include/ArcadeContent.cpp \
			../../include/AGameModule.cpp \
			../../include/AModule.cpp \
			../../include/Exception.cpp \

OBJ		=	$(SRC:.cpp=.o)

NAME	=	../lib_arcade_space_invader.so

CXX         =	g++
CXXFLAGS    =	-I./ -I../../include -fPIC -pipe -g -Wall

all: $(NAME)

$(NAME):	$(OBJ)
	$(CXX) -shared -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) vgcore.*

re: fclean all

.PHONY: clean re fclean all
